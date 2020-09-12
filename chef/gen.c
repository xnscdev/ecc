/*************************************************************************
 * This file is part of ECC.                                             *
 * Copyright (C) 2020 XNSC                                               *
 *                                                                       *
 * This program is free software: you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program. If not, see <https://www.gnu.org/licenses/>. *
 *************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libecc/errors.h>
#include <libecc/strutils.h>
#include <libecc/xalloca.h>
#include <libgccjit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chef.h"

#define MAX_CONTAINER_COUNT 64

char *srcfile;

struct ingredient_map
{
  struct ingredient *ing;
  gcc_jit_lvalue *var;
  struct ingredient_map *next;
};

static struct ingredient_map *ings;
static struct strlist *verbs;

static gcc_jit_type *type_void;
static gcc_jit_type *type_void_ptr;
static gcc_jit_type *type_int;
static gcc_jit_type *type_unsigned;
static gcc_jit_type *type_container_ptr;
static gcc_jit_type *type_size_t;
static gcc_jit_type *type_size_t_ptr;
static gcc_jit_type *type_const_char_ptr;
static gcc_jit_field *field_value;
static gcc_jit_field *field_type;
static gcc_jit_field *field_next;
static gcc_jit_function *func_malloc;
static gcc_jit_function *func_free;
static gcc_jit_function *func_scanf;
static gcc_jit_function *func_getchar;
static gcc_jit_function *func_putchar;
static gcc_jit_function *func_printf;
static gcc_jit_function *func_rand;
static gcc_jit_function *func_srand;
static gcc_jit_function *func_time;
static gcc_jit_function *func_push;
static gcc_jit_function *func_pop;
static gcc_jit_function *func_pop_dish;
static gcc_jit_function *func_read_int;
static gcc_jit_function *func_add_dry;
static gcc_jit_function *func_liquefy;
static gcc_jit_function *func_stir;
static gcc_jit_function *func_mix;
static gcc_jit_function *func_pour;
static gcc_jit_function *func_print_dish;
static gcc_jit_lvalue *var_bowls;
static gcc_jit_lvalue *var_dishes;

static void add_instruction (gcc_jit_context *ctx, gcc_jit_block *block);

static gcc_jit_rvalue *
gcc_jit_type_sizeof (gcc_jit_context *ctx, gcc_jit_location *loc,
		     gcc_jit_type *type)
{
  const void *nullptr = 0;
  gcc_jit_type *type_ptr = gcc_jit_type_get_pointer (type);
  gcc_jit_type *type_byte_ptr =
    gcc_jit_type_get_pointer (gcc_jit_context_get_int_type (ctx, 1, 0));
  gcc_jit_rvalue *one = gcc_jit_context_one (ctx, type_size_t);
  gcc_jit_rvalue *ptr0 =
    gcc_jit_context_new_rvalue_from_ptr (ctx, type_ptr, &nullptr);
  gcc_jit_rvalue *ptr1 =
    gcc_jit_lvalue_get_address (gcc_jit_context_new_array_access (ctx, loc,
								  ptr0, one),
				 NULL);
  ptr0 = gcc_jit_context_new_cast (ctx, loc, ptr0, type_byte_ptr);
  ptr1 = gcc_jit_context_new_cast (ctx, loc, ptr1, type_byte_ptr);
  return gcc_jit_context_new_binary_op (ctx, loc, GCC_JIT_BINARY_OP_MINUS,
					type_size_t, ptr1, ptr0);
}

static gcc_jit_function *
gen_func_push (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_id =
    gcc_jit_context_new_param (ctx, loc, type_int, "id");
  gcc_jit_param *param_value =
    gcc_jit_context_new_param (ctx, loc, type_int, "value");
  gcc_jit_param *param_type =
    gcc_jit_context_new_param (ctx, loc, type_int, "type");
  gcc_jit_param *params[3] = {param_id, param_value, param_type};
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_void, "push", 3, params, 0);
  gcc_jit_lvalue *container =
    gcc_jit_function_new_local (func, loc, type_container_ptr,
				"container");
  gcc_jit_block *block_entry =
    gcc_jit_function_new_block (func, "entry");
  gcc_jit_lvalue *container_value =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (container),
				      loc, field_value);
  gcc_jit_lvalue *container_type =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (container),
				      loc, field_type);
  gcc_jit_lvalue *container_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (container),
				      loc, field_next);
  gcc_jit_rvalue *size = gcc_jit_type_sizeof (ctx, loc, type_size_t);
  gcc_jit_rvalue *malloc_call =
    gcc_jit_context_new_call (ctx, loc, func_malloc, 1, &size);
  gcc_jit_rvalue *container_cast =
    gcc_jit_context_new_cast (ctx, loc, malloc_call, type_container_ptr);
  gcc_jit_lvalue *target_container =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_bowls),
				      gcc_jit_param_as_rvalue (param_id));

  gcc_jit_block_add_assignment (block_entry, loc, container, container_cast);
  gcc_jit_block_add_assignment (block_entry, loc, container_value,
				gcc_jit_param_as_rvalue (param_value));
  gcc_jit_block_add_assignment (block_entry, loc, container_type,
				gcc_jit_param_as_rvalue (param_type));
  gcc_jit_block_add_assignment (block_entry, loc, container_next,
				gcc_jit_lvalue_as_rvalue (target_container));
  gcc_jit_block_add_assignment (block_entry, loc, target_container,
				gcc_jit_lvalue_as_rvalue (container));
  gcc_jit_block_end_with_void_return (block_entry, loc);
  return func;
}

static gcc_jit_function *
gen_func_pop (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_id =
    gcc_jit_context_new_param (ctx, loc, type_int, "id");
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_container_ptr, "pop", 1, &param_id, 0);
  gcc_jit_lvalue *container =
    gcc_jit_function_new_local (func, loc, type_container_ptr,
				"container");
  gcc_jit_block *block_entry =
    gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_null = gcc_jit_function_new_block (func, "null");
  gcc_jit_block *block_shift =
    gcc_jit_function_new_block (func, "shift");
  gcc_jit_lvalue *target_container =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_bowls),
				      gcc_jit_param_as_rvalue (param_id));
  gcc_jit_rvalue *container_null =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (container),
				    gcc_jit_context_null (ctx,
							  type_container_ptr));
  gcc_jit_lvalue *target_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue
				      (target_container), loc, field_next);
  
  gcc_jit_block_add_assignment (block_entry, loc, container,
				gcc_jit_lvalue_as_rvalue (target_container));
  gcc_jit_block_end_with_conditional (block_entry, loc, container_null,
				      block_null, block_shift);
  gcc_jit_block_end_with_return (block_null, loc,
				 gcc_jit_context_null (ctx,
						       type_container_ptr));
  gcc_jit_block_add_assignment (block_shift, loc, target_container,
				gcc_jit_lvalue_as_rvalue (target_next));
  gcc_jit_block_end_with_return (block_shift, loc,
				 gcc_jit_lvalue_as_rvalue (container));
  return func;
}

static gcc_jit_function *
gen_func_pop_dish (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_id =
    gcc_jit_context_new_param (ctx, loc, type_int, "id");
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_container_ptr, "pop_dish", 1,
				  &param_id, 0);
  gcc_jit_lvalue *container =
    gcc_jit_function_new_local (func, loc, type_container_ptr,
				"container");
  gcc_jit_block *block_entry =
    gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_null = gcc_jit_function_new_block (func, "null");
  gcc_jit_block *block_shift =
    gcc_jit_function_new_block (func, "shift");
  gcc_jit_lvalue *target_container =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_dishes),
				      gcc_jit_param_as_rvalue (param_id));
  gcc_jit_rvalue *container_null =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (container),
				    gcc_jit_context_null (ctx,
							  type_container_ptr));
  gcc_jit_lvalue *target_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue
				      (target_container), loc, field_next);
  
  gcc_jit_block_add_assignment (block_entry, loc, container,
				gcc_jit_lvalue_as_rvalue (target_container));
  gcc_jit_block_end_with_conditional (block_entry, loc, container_null,
				      block_null, block_shift);
  gcc_jit_block_end_with_return (block_null, loc,
				 gcc_jit_context_null (ctx,
						       type_container_ptr));
  gcc_jit_block_add_assignment (block_shift, loc, target_container,
				gcc_jit_lvalue_as_rvalue (target_next));
  gcc_jit_block_end_with_return (block_shift, loc,
				 gcc_jit_lvalue_as_rvalue (container));
  return func;
}

static gcc_jit_function *
gen_func_read_int (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_dest =
    gcc_jit_context_new_param (ctx, loc, gcc_jit_type_get_pointer (type_int),
			       "dest");
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_void, "read_int", 1, &param_dest, 0);
  gcc_jit_block *block_entry = gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_fail = gcc_jit_function_new_block (func, "fail");
  gcc_jit_block *block_done = gcc_jit_function_new_block (func, "done");
  gcc_jit_rvalue *fmt_string =
    gcc_jit_context_new_string_literal (ctx, "%d");
  gcc_jit_rvalue *var_dest = gcc_jit_param_as_rvalue (param_dest);
  gcc_jit_rvalue *scanf_call_args[2] = {fmt_string, var_dest};
  gcc_jit_rvalue *scanf_call =
    gcc_jit_context_new_call (ctx, loc, func_scanf, 2, scanf_call_args);
  gcc_jit_rvalue *scanf_done =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_LT,
				    scanf_call,
				    gcc_jit_context_one (ctx, type_int));
  gcc_jit_rvalue *getchar_call =
    gcc_jit_context_new_call (ctx, loc, func_getchar, 0, NULL);
  gcc_jit_rvalue *newline_char =
    gcc_jit_context_new_rvalue_from_int (ctx, type_int, '\n');
  gcc_jit_rvalue *getchar_done =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    getchar_call, newline_char);
  gcc_jit_block_end_with_conditional (block_entry, loc, scanf_done,
				      block_fail, block_done);
  gcc_jit_block_end_with_conditional (block_fail, loc, getchar_done,
				      block_entry, block_fail);
  gcc_jit_block_end_with_void_return (block_done, loc);
  return func;
}

static gcc_jit_function *
gen_func_add_dry (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_bowl =
    gcc_jit_context_new_param (ctx, loc, type_int, "bowl");
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_void, "add_dry", 1, &param_bowl, 0);
  gcc_jit_lvalue *var_temp =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "temp");
  gcc_jit_lvalue *var_total =
    gcc_jit_function_new_local (func, loc, type_int, "total");
  gcc_jit_block *block_entry = gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_check = gcc_jit_function_new_block (func, "check");
  gcc_jit_block *block_add = gcc_jit_function_new_block (func, "add");
  gcc_jit_block *block_next = gcc_jit_function_new_block (func, "next");
  gcc_jit_block *block_done = gcc_jit_function_new_block (func, "done");
  gcc_jit_rvalue *null = gcc_jit_context_null (ctx, type_container_ptr);
  gcc_jit_rvalue *push_call_args[3] = {
    gcc_jit_param_as_rvalue (param_bowl),
    gcc_jit_lvalue_as_rvalue (var_total),
    gcc_jit_context_zero (ctx, type_int)
  };
  gcc_jit_lvalue *var_bowl =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_bowls),
				      gcc_jit_param_as_rvalue (param_bowl));
  gcc_jit_rvalue *condition =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (var_temp),
				    null);
  gcc_jit_lvalue *temp_value =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_value);
  gcc_jit_lvalue *temp_type =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_type);
  gcc_jit_lvalue *temp_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_next);
  gcc_jit_rvalue *check_dry =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (temp_type),
				    gcc_jit_context_zero (ctx, type_int));
  gcc_jit_block_add_assignment (block_entry, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (var_bowl));
  gcc_jit_block_add_assignment (block_entry, loc, var_total,
				gcc_jit_context_zero (ctx, type_int));
  gcc_jit_block_end_with_conditional (block_entry, loc, condition,
				      block_done, block_check);
  gcc_jit_block_end_with_conditional (block_check, loc, check_dry,
				      block_add, block_next);
  gcc_jit_block_add_assignment_op (block_add, loc, var_total,
				   GCC_JIT_BINARY_OP_PLUS,
				   gcc_jit_lvalue_as_rvalue (temp_value));
  gcc_jit_block_end_with_jump (block_add, loc, block_next);
  gcc_jit_block_add_assignment (block_next, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (temp_next));
  gcc_jit_block_end_with_conditional (block_next, loc, condition,
				      block_done, block_check);
  gcc_jit_block_add_eval (block_done, loc,
			  gcc_jit_context_new_call (ctx, loc, func_push, 3,
						    push_call_args));
  gcc_jit_block_end_with_void_return (block_done, loc);
  return func;
}

static gcc_jit_function *
gen_func_liquefy (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_bowl =
    gcc_jit_context_new_param (ctx, loc, type_int, "bowl");
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_void, "liquefy", 1, &param_bowl, 0);
  gcc_jit_lvalue *var_temp =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "temp");
  gcc_jit_block *block_entry = gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_next = gcc_jit_function_new_block (func, "next");
  gcc_jit_block *block_liquefy =
    gcc_jit_function_new_block (func, "liquefy");
  gcc_jit_block *block_done = gcc_jit_function_new_block (func, "done");
  gcc_jit_rvalue *null = gcc_jit_context_null (ctx, type_container_ptr);
  gcc_jit_lvalue *var_bowl =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_bowls),
				      gcc_jit_param_as_rvalue (param_bowl));
  gcc_jit_lvalue *temp_type =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_type);
  gcc_jit_lvalue *temp_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_next);
  gcc_jit_rvalue *condition =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (var_temp),
				    null);
  gcc_jit_block_add_assignment (block_entry, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (var_bowl));
  gcc_jit_block_end_with_conditional (block_entry, loc, condition,
				      block_done, block_liquefy);
  gcc_jit_block_add_assignment (block_next, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (temp_next));
  gcc_jit_block_end_with_conditional (block_next, loc, condition,
				      block_done, block_liquefy);
  gcc_jit_block_add_assignment (block_liquefy, loc, temp_type,
				gcc_jit_context_one (ctx, type_int));
  gcc_jit_block_end_with_jump (block_liquefy, loc, block_next);
  gcc_jit_block_end_with_void_return (block_done, loc);
  return func;
}

static gcc_jit_function *
gen_func_stir (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_bowl =
    gcc_jit_context_new_param (ctx, loc, type_int, "bowl");
  gcc_jit_param *param_depth =
    gcc_jit_context_new_param (ctx, loc, type_int, "depth");
  gcc_jit_param *params[2] = {param_bowl, param_depth};
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_void, "stir", 2, params, 0);
  gcc_jit_lvalue *var_save =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "save");
  gcc_jit_lvalue *var_temp =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "temp");
  gcc_jit_lvalue *var_c =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "c");
  gcc_jit_lvalue *var_i =
    gcc_jit_function_new_local (func, loc, type_int, "i");
  gcc_jit_block *block_entry = gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_pop = gcc_jit_function_new_block (func, "pop");
  gcc_jit_block *block_next = gcc_jit_function_new_block (func, "next");
  gcc_jit_block *block_insert = gcc_jit_function_new_block (func, "insert");
  gcc_jit_block *block_done = gcc_jit_function_new_block (func, "done");
  gcc_jit_lvalue *var_bowl =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_bowls),
				      gcc_jit_param_as_rvalue (param_bowl));
  gcc_jit_rvalue *null = gcc_jit_context_null (ctx, type_container_ptr);
  gcc_jit_rvalue *save_condition =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (var_save),
				    null);
  gcc_jit_rvalue *depth_condition =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_GE,
				    gcc_jit_lvalue_as_rvalue (var_i),
				    gcc_jit_param_as_rvalue (param_depth));
  gcc_jit_lvalue *temp_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_next);
  gcc_jit_lvalue *save_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_save),
				      loc, field_next);
  gcc_jit_block_add_assignment (block_entry, loc, var_i,
				gcc_jit_context_zero (ctx, type_int));
  gcc_jit_block_add_assignment (block_entry, loc, var_save,
				gcc_jit_lvalue_as_rvalue (var_bowl));
  gcc_jit_block_end_with_conditional (block_entry, loc, save_condition,
				      block_done, block_pop);
  gcc_jit_block_add_assignment (block_pop, loc, var_bowl,
				gcc_jit_lvalue_as_rvalue (save_next));
  gcc_jit_block_add_assignment (block_pop, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (save_next));
  gcc_jit_block_end_with_conditional (block_pop, loc, depth_condition,
				      block_insert, block_next);
  gcc_jit_block_add_assignment_op (block_next, loc, var_i,
				   GCC_JIT_BINARY_OP_PLUS,
				   gcc_jit_context_one (ctx, type_int));
  gcc_jit_block_add_assignment (block_next, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (temp_next));
  gcc_jit_block_end_with_conditional (block_next, loc, depth_condition,
				      block_insert, block_next);
  gcc_jit_block_add_assignment (block_insert, loc, var_c,
				gcc_jit_lvalue_as_rvalue (temp_next));
  gcc_jit_block_add_assignment (block_insert, loc, temp_next,
				gcc_jit_lvalue_as_rvalue (var_save));
  gcc_jit_block_add_assignment (block_insert, loc, save_next,
				gcc_jit_lvalue_as_rvalue (var_c));
  gcc_jit_block_end_with_void_return (block_insert, loc);
  gcc_jit_block_end_with_void_return (block_done, loc);
  return func;
}

static gcc_jit_function *
gen_func_mix (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_bowl =
    gcc_jit_context_new_param (ctx, loc, type_int, "bowl");
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_void, "mix", 1, &param_bowl, 0);
  gcc_jit_lvalue *var_arr =
    gcc_jit_function_new_local (func, loc,
				gcc_jit_type_get_pointer (type_container_ptr),
				"arr");
  gcc_jit_lvalue *var_temp =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "temp");
  gcc_jit_lvalue *var_len =
    gcc_jit_function_new_local (func, loc, type_int, "len");
  gcc_jit_lvalue *var_index =
    gcc_jit_function_new_local (func, loc, type_int, "index");
  gcc_jit_lvalue *var_i =
    gcc_jit_function_new_local (func, loc, type_int, "i");
  gcc_jit_block *block_entry = gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_check_len =
    gcc_jit_function_new_block (func, "check_len");
  gcc_jit_block *block_copy = gcc_jit_function_new_block (func, "copy");
  gcc_jit_block *block_next_copy =
    gcc_jit_function_new_block (func, "next_copy");
  gcc_jit_block *block_shuffle =
    gcc_jit_function_new_block (func, "shuffle");
  gcc_jit_block *block_next_shuffle =
    gcc_jit_function_new_block (func, "next_shuffle");
  gcc_jit_block *block_link = gcc_jit_function_new_block (func, "link");
  gcc_jit_block *block_next_link =
    gcc_jit_function_new_block (func, "next_link");
  gcc_jit_block *block_done = gcc_jit_function_new_block (func, "done");
  gcc_jit_lvalue *temp_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_next);
  gcc_jit_lvalue *var_bowl =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_bowls),
				      gcc_jit_param_as_rvalue (param_bowl));
  gcc_jit_rvalue *null = gcc_jit_context_null (ctx, type_container_ptr);
  gcc_jit_rvalue *arr_null =
    gcc_jit_context_null (ctx, gcc_jit_type_get_pointer (type_container_ptr));
  gcc_jit_rvalue *temp_condition =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (var_temp),
				    null);
  gcc_jit_rvalue *len_condition =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_LT,
				    gcc_jit_lvalue_as_rvalue (var_i),
				    gcc_jit_lvalue_as_rvalue (var_len));
  gcc_jit_rvalue *cast_len =
    gcc_jit_context_new_cast (ctx, loc, gcc_jit_lvalue_as_rvalue (var_len),
			      type_size_t);
  gcc_jit_rvalue *arr_size =
    gcc_jit_context_new_binary_op (ctx, loc, GCC_JIT_BINARY_OP_MULT,
				   type_size_t,
				   gcc_jit_type_sizeof (ctx, loc,
							type_container_ptr),
				   cast_len);
  gcc_jit_rvalue *malloc_call =
    gcc_jit_context_new_call (ctx, loc, func_malloc, 1, &arr_size);
  gcc_jit_rvalue *cast_malloc =
    gcc_jit_context_new_cast (ctx, loc, malloc_call,
			      gcc_jit_type_get_pointer (type_container_ptr));
  gcc_jit_rvalue *rvalue_arr = gcc_jit_lvalue_as_rvalue (var_arr);
  gcc_jit_lvalue *arr_i =
    gcc_jit_context_new_array_access (ctx, loc, rvalue_arr,
				      gcc_jit_lvalue_as_rvalue (var_i));
  gcc_jit_lvalue *arr_index =
    gcc_jit_context_new_array_access (ctx, loc, rvalue_arr,
				      gcc_jit_lvalue_as_rvalue (var_index));
  gcc_jit_rvalue *len_diff =
    gcc_jit_context_new_binary_op (ctx, loc, GCC_JIT_BINARY_OP_MINUS,
				   type_int,
				   gcc_jit_lvalue_as_rvalue (var_len),
				   gcc_jit_lvalue_as_rvalue (var_i));
  gcc_jit_rvalue *scaled_rand =
    gcc_jit_context_new_binary_op (ctx, loc, GCC_JIT_BINARY_OP_MODULO,
				   type_int,
				   gcc_jit_context_new_call (ctx, loc,
							     func_rand,
							     0, NULL),
				   len_diff);
  gcc_jit_rvalue *rand_index =
    gcc_jit_context_new_binary_op (ctx, loc, GCC_JIT_BINARY_OP_PLUS,
				   type_int,
				   gcc_jit_lvalue_as_rvalue (var_i),
				   scaled_rand);
  gcc_jit_lvalue *arr_first =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_arr),
				      gcc_jit_context_zero (ctx, type_int));
  gcc_jit_block_add_assignment (block_entry, loc, var_len,
				gcc_jit_context_zero (ctx, type_int));
  gcc_jit_block_add_assignment (block_entry, loc, var_arr, arr_null);
  gcc_jit_block_add_assignment (block_entry, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (var_bowl));
  gcc_jit_block_end_with_conditional (block_entry, loc, temp_condition,
				      block_done, block_check_len);
  gcc_jit_block_add_assignment_op (block_check_len, loc, var_len,
				   GCC_JIT_BINARY_OP_PLUS,
				   gcc_jit_context_one (ctx, type_int));
  gcc_jit_block_add_assignment (block_check_len, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (temp_next));
  gcc_jit_block_end_with_conditional (block_check_len, loc, temp_condition,
				      block_copy, block_check_len);
  gcc_jit_block_add_assignment (block_copy, loc, var_i,
				gcc_jit_context_zero (ctx, type_int));
  gcc_jit_block_add_assignment (block_copy, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (var_bowl));
  gcc_jit_block_add_assignment (block_copy, loc, var_arr, cast_malloc);
  gcc_jit_block_end_with_jump (block_copy, loc, block_next_copy);
  gcc_jit_block_add_assignment (block_next_copy, loc, arr_i,
				gcc_jit_lvalue_as_rvalue (var_temp));
  gcc_jit_block_add_assignment (block_next_copy, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (temp_next));
  gcc_jit_block_add_assignment_op (block_next_copy, loc, var_i,
				   GCC_JIT_BINARY_OP_PLUS,
				   gcc_jit_context_one (ctx, type_int));
  gcc_jit_block_end_with_conditional (block_next_copy, loc, len_condition,
				      block_next_copy, block_shuffle);
  gcc_jit_block_add_assignment (block_shuffle, loc, var_i,
				gcc_jit_context_zero (ctx, type_int));
  gcc_jit_block_end_with_jump (block_shuffle, loc, block_next_shuffle);
  gcc_jit_block_add_assignment (block_next_shuffle, loc, var_index,
				rand_index);
  gcc_jit_block_add_assignment (block_next_shuffle, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (arr_index));
  gcc_jit_block_add_assignment (block_next_shuffle, loc, arr_index,
				gcc_jit_lvalue_as_rvalue (arr_i));
  gcc_jit_block_add_assignment (block_next_shuffle, loc, arr_i,
				gcc_jit_lvalue_as_rvalue (var_temp));
  gcc_jit_block_add_assignment_op (block_next_shuffle, loc, var_i,
				   GCC_JIT_BINARY_OP_PLUS,
				   gcc_jit_context_one (ctx, type_int));
  gcc_jit_block_end_with_conditional (block_next_shuffle, loc, len_condition,
				      block_next_shuffle, block_link);
  gcc_jit_block_add_assignment (block_link, loc, var_bowl,
				gcc_jit_lvalue_as_rvalue (arr_first));
  gcc_jit_block_add_assignment (block_link, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (var_bowl));
  gcc_jit_block_add_assignment (block_link, loc, var_i,
				gcc_jit_context_one (ctx, type_int));
  gcc_jit_block_end_with_conditional (block_link, loc, len_condition,
				      block_next_link, block_done);
  gcc_jit_block_add_assignment (block_next_link, loc, temp_next,
				gcc_jit_lvalue_as_rvalue (arr_i));
  gcc_jit_block_add_assignment (block_next_link, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (temp_next));
  gcc_jit_block_add_assignment_op (block_next_link, loc, var_i,
				   GCC_JIT_BINARY_OP_PLUS,
				   gcc_jit_context_one (ctx, type_int));
  gcc_jit_block_end_with_conditional (block_next_link, loc, len_condition,
				      block_next_link, block_done);
  gcc_jit_block_add_assignment (block_done, loc, temp_next, null);
  gcc_jit_block_add_eval (block_done, loc,
			  gcc_jit_context_new_call (ctx, loc, func_free,
						    1, &rvalue_arr));
  gcc_jit_block_end_with_void_return (block_done, loc);
  return func;
}

static gcc_jit_function *
gen_func_pour (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_bowl =
    gcc_jit_context_new_param (ctx, loc, type_int, "bowl");
  gcc_jit_param *param_dish =
    gcc_jit_context_new_param (ctx, loc, type_int, "dish");
  gcc_jit_param *params[2] = {param_bowl, param_dish};
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_void, "pour", 2, params, 0);
  gcc_jit_lvalue *var_save =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "save");
  gcc_jit_lvalue *var_temp =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "temp");
  gcc_jit_lvalue *var_new =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "new");
  gcc_jit_lvalue *var_c =
    gcc_jit_function_new_local (func, loc, type_container_ptr, "c");
  gcc_jit_block *block_entry = gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_start = gcc_jit_function_new_block (func, "start");
  gcc_jit_block *block_next = gcc_jit_function_new_block (func, "next");
  gcc_jit_block *block_push = gcc_jit_function_new_block (func, "push");
  gcc_jit_block *block_done = gcc_jit_function_new_block (func, "done");
  gcc_jit_lvalue *var_bowl =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_bowls),
				      gcc_jit_param_as_rvalue (param_bowl));
  gcc_jit_lvalue *var_dish =
    gcc_jit_context_new_array_access (ctx, loc,
				      gcc_jit_lvalue_as_rvalue (var_dishes),
				      gcc_jit_param_as_rvalue (param_dish));
  gcc_jit_rvalue *size = gcc_jit_type_sizeof (ctx, loc, type_size_t);
  gcc_jit_rvalue *malloc_call =
    gcc_jit_context_new_call (ctx, loc, func_malloc, 1, &size);
  gcc_jit_rvalue *container_cast =
    gcc_jit_context_new_cast (ctx, loc, malloc_call, type_container_ptr);
  gcc_jit_lvalue *new_value =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_new),
				      loc, field_value);
  gcc_jit_lvalue *temp_value =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_value);
  gcc_jit_lvalue *c_value =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_c),
				      loc, field_value);
  gcc_jit_lvalue *new_type =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_new),
				      loc, field_type);
  gcc_jit_lvalue *temp_type =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_type);
  gcc_jit_lvalue *c_type =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_c),
				      loc, field_type);
  gcc_jit_lvalue *new_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_new),
				      loc, field_next);
  gcc_jit_lvalue *temp_next =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      loc, field_next);
  gcc_jit_rvalue *null = gcc_jit_context_null (ctx, type_container_ptr);
  gcc_jit_rvalue *condition =
    gcc_jit_context_new_comparison (ctx, loc, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (var_temp),
				    null);
  gcc_jit_block_add_assignment (block_entry, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (var_bowl));
  gcc_jit_block_end_with_conditional (block_entry, loc, condition,
				      block_done, block_start);
  gcc_jit_block_add_assignment (block_start, loc, var_new, container_cast);
  gcc_jit_block_add_assignment (block_start, loc, var_save,
				gcc_jit_lvalue_as_rvalue (var_new));
  gcc_jit_block_add_assignment (block_start, loc, new_value,
				gcc_jit_lvalue_as_rvalue (temp_value));
  gcc_jit_block_add_assignment (block_start, loc, new_type,
				gcc_jit_lvalue_as_rvalue (temp_type));
  gcc_jit_block_end_with_jump (block_start, loc, block_next);
  gcc_jit_block_add_assignment (block_next, loc, var_temp,
				gcc_jit_lvalue_as_rvalue (temp_next));
  gcc_jit_block_end_with_conditional (block_next, loc, condition, block_done,
				      block_push);
  gcc_jit_block_add_assignment (block_push, loc, var_c, container_cast);
  gcc_jit_block_add_assignment (block_push, loc, c_value,
				gcc_jit_lvalue_as_rvalue (temp_value));
  gcc_jit_block_add_assignment (block_push, loc, c_type,
				gcc_jit_lvalue_as_rvalue (temp_type));
  gcc_jit_block_add_assignment (block_push, loc, new_next,
				gcc_jit_lvalue_as_rvalue (var_c));
  gcc_jit_block_add_assignment (block_push, loc, var_new,
				gcc_jit_lvalue_as_rvalue (var_c));
  gcc_jit_block_end_with_jump (block_push, loc, block_next);
  gcc_jit_block_add_assignment (block_done, loc, new_next,
				gcc_jit_lvalue_as_rvalue (var_dish));
  gcc_jit_block_add_assignment (block_done, loc, var_dish,
				gcc_jit_lvalue_as_rvalue (var_save));
  gcc_jit_block_end_with_void_return (block_done, loc);
  return func;
}

static gcc_jit_function *
gen_func_print_dish (gcc_jit_context *ctx, gcc_jit_location *loc)
{
  gcc_jit_param *param_dish =
    gcc_jit_context_new_param (ctx, loc, type_int, "dish");
  gcc_jit_function *func =
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_EXPORTED,
				  type_void, "print_dish", 1, &param_dish, 0);
  gcc_jit_lvalue *var_temp =
    gcc_jit_function_new_local (func, NULL, type_container_ptr, "temp");
  gcc_jit_block *block_entry = gcc_jit_function_new_block (func, "entry");
  gcc_jit_block *block_print = gcc_jit_function_new_block (func, "print");
  gcc_jit_block *block_print_num =
    gcc_jit_function_new_block (func, "print_num");
  gcc_jit_block *block_print_char =
    gcc_jit_function_new_block (func, "print_char");
  gcc_jit_block *block_done = gcc_jit_function_new_block (func, "done");
  gcc_jit_rvalue *null = gcc_jit_context_null (ctx, type_container_ptr);
  gcc_jit_rvalue *done_condition =
    gcc_jit_context_new_comparison (ctx, NULL, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (var_temp),
				    null);
  gcc_jit_lvalue *var_type =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      NULL, field_type);
  gcc_jit_lvalue *var_value =
    gcc_jit_rvalue_dereference_field (gcc_jit_lvalue_as_rvalue (var_temp),
				      NULL, field_value);
  gcc_jit_rvalue *print_condition =
    gcc_jit_context_new_comparison (ctx, NULL, GCC_JIT_COMPARISON_EQ,
				    gcc_jit_lvalue_as_rvalue (var_type),
				    gcc_jit_context_zero (ctx, type_int));
  gcc_jit_rvalue *printf_fmt = gcc_jit_context_new_string_literal (ctx, "%d");
  gcc_jit_rvalue *printf_call_args[2] = {
    printf_fmt,
    gcc_jit_lvalue_as_rvalue (var_value)
  };
  gcc_jit_rvalue *printf_call =
    gcc_jit_context_new_call (ctx, NULL, func_printf, 2, printf_call_args);
  gcc_jit_rvalue *putchar_call_arg = gcc_jit_lvalue_as_rvalue (var_value);
  gcc_jit_rvalue *putchar_call =
    gcc_jit_context_new_call (ctx, NULL, func_putchar, 1, &putchar_call_arg);
  gcc_jit_rvalue *pop_call_arg = gcc_jit_param_as_rvalue (param_dish);
  gcc_jit_rvalue *pop_call =
    gcc_jit_context_new_call (ctx, NULL, func_pop_dish, 1, &pop_call_arg);
  gcc_jit_block_add_assignment (block_entry, NULL, var_temp, pop_call);
  gcc_jit_block_end_with_conditional (block_entry, NULL, done_condition,
				      block_done, block_print);
  gcc_jit_block_end_with_conditional (block_print, NULL, print_condition,
				      block_print_num, block_print_char);
  gcc_jit_block_add_eval (block_print_num, NULL, printf_call);
  gcc_jit_block_end_with_jump (block_print_num, NULL, block_entry);
  gcc_jit_block_add_eval (block_print_char, NULL, putchar_call);
  gcc_jit_block_end_with_jump (block_print_char, NULL, block_entry);
  gcc_jit_block_end_with_void_return (block_done, NULL);
  return func;
}

static void
gen_prog_start (gcc_jit_context *ctx)
{
  gcc_jit_struct *struct_container =
    gcc_jit_context_new_opaque_struct (ctx, NULL, "container");
  gcc_jit_field *container_fields[3];
  gcc_jit_type *type_container = gcc_jit_struct_as_type (struct_container);
  gcc_jit_type *type_container_ptr_arr;
  gcc_jit_param *param_size =
    gcc_jit_context_new_param (ctx, NULL, type_size_t, "size");
  gcc_jit_param *param_fmt_scanf =
    gcc_jit_context_new_param (ctx, NULL, type_const_char_ptr, "fmt");
  gcc_jit_param *param_fmt_printf =
    gcc_jit_context_new_param (ctx, NULL, type_const_char_ptr, "fmt");
  gcc_jit_param *param_c =
    gcc_jit_context_new_param (ctx, NULL, type_int, "c");
  gcc_jit_param *param_ptr =
    gcc_jit_context_new_param (ctx, NULL, type_void_ptr, "ptr");
  gcc_jit_param *param_seed =
    gcc_jit_context_new_param (ctx, NULL, type_unsigned, "seed");
  gcc_jit_param *param_second =
    gcc_jit_context_new_param (ctx, NULL, type_size_t_ptr, "second");

  func_malloc =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_void_ptr, "malloc", 1, &param_size, 0);
  func_free =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_void, "free", 1, &param_ptr, 0);
  func_scanf =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_int, "scanf", 1, &param_fmt_scanf, 1);
  func_getchar =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_int, "getchar", 0, NULL, 0);
  func_putchar =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_int, "putchar", 1, &param_c, 0);
  func_printf =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_int, "printf", 1, &param_fmt_printf,
				  1);
  func_rand =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_int, "rand", 0, NULL, 0);
  func_srand =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_void, "srand", 1, &param_seed, 0);
  func_time =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_size_t, "time", 1, &param_second, 0);
  
  type_container_ptr = gcc_jit_type_get_pointer (type_container);
  type_container_ptr_arr =
    gcc_jit_context_new_array_type (ctx, NULL, type_container_ptr,
				    MAX_CONTAINER_COUNT);
  field_value = gcc_jit_context_new_field (ctx, NULL, type_int, "value");
  field_type = gcc_jit_context_new_field (ctx, NULL, type_int, "type");
  field_next = gcc_jit_context_new_field (ctx, NULL,
					  type_container_ptr, "next");
  container_fields[0] = field_value;
  container_fields[1] = field_type;
  container_fields[2] = field_next;
  gcc_jit_struct_set_fields (struct_container, NULL, 3,
			     container_fields);

  var_bowls = gcc_jit_context_new_global (ctx, NULL, GCC_JIT_GLOBAL_INTERNAL,
					  type_container_ptr_arr, "bowls");
  var_dishes = gcc_jit_context_new_global (ctx, NULL, GCC_JIT_GLOBAL_INTERNAL,
					   type_container_ptr_arr, "dishes");
  
  func_push = gen_func_push (ctx, NULL);
  func_pop = gen_func_pop (ctx, NULL);
  func_pop_dish = gen_func_pop_dish (ctx, NULL);
  func_read_int = gen_func_read_int (ctx, NULL);
  func_add_dry = gen_func_add_dry (ctx, NULL);
  func_liquefy = gen_func_liquefy (ctx, NULL);
  func_stir = gen_func_stir (ctx, NULL);
  func_mix = gen_func_mix (ctx, NULL);
  func_pour = gen_func_pour (ctx, NULL);
  func_print_dish = gen_func_print_dish (ctx, NULL);
}

static void
add_inst_take (gcc_jit_context *ctx, gcc_jit_block *block)
{
  struct ingredient_map *map;
  for (map = ings; map != NULL; map = map->next)
    {
      if (strcmp (map->ing->name, rcp->method->ing) == 0)
	{
	  gcc_jit_rvalue *var_dest =
	    gcc_jit_lvalue_get_address (map->var, NULL);
	  gcc_jit_rvalue *read_int_call =
	    gcc_jit_context_new_call (ctx, NULL, func_read_int, 1, &var_dest);
	  gcc_jit_block_add_eval (block, NULL, read_int_call);
	}
    }
  if (map == NULL)
    {
      gcc_jit_lvalue *global_new =
	gcc_jit_context_new_global (ctx, NULL, GCC_JIT_GLOBAL_INTERNAL,
				    type_int, rcp->method->ing);
      gcc_jit_rvalue *var_dest =
	gcc_jit_lvalue_get_address (global_new, NULL);
      gcc_jit_rvalue *read_int_call =
	gcc_jit_context_new_call (ctx, NULL, func_read_int, 1, &var_dest);
      struct ingredient_map *temp = xmalloc (sizeof (struct ingredient_map));
      temp->ing = xmalloc (sizeof (struct ingredient));
      temp->ing->name = rcp->method->ing;
      temp->ing->initval = 0;
      temp->ing->type = MEASURE_DRY;
      temp->var = global_new;
      temp->next = ings;
      ings = temp;
      gcc_jit_block_add_eval (block, NULL, read_int_call);
    }
}

static void
add_inst_put (gcc_jit_context *ctx, gcc_jit_block *block)
{
  gcc_jit_rvalue *call_args[3] = {
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->bowl - 1),
    NULL,
    NULL
  };
  gcc_jit_rvalue *push_call;
  struct ingredient_map *map;
  for (map = ings; map != NULL; map = map->next)
    {
      if (strcmp (map->ing->name, rcp->method->ing) == 0)
	{
	  call_args[1] = gcc_jit_lvalue_as_rvalue (map->var);
	  if (map->ing->type == MEASURE_LIQUID)
	    call_args[2] = gcc_jit_context_one (ctx, type_int);
	  else
	    call_args[2] = gcc_jit_context_zero (ctx, type_int);
	  break;
	}
    }
  
  if (call_args[1] == NULL || call_args[2] == NULL)
    error ("undefined ingredient: %s", rcp->method->ing);

  push_call = gcc_jit_context_new_call (ctx, NULL, func_push, 3, call_args);
  gcc_jit_block_add_eval (block, NULL, push_call);
}

static void
add_inst_fold (gcc_jit_context *ctx, gcc_jit_block *block)
{
  struct ingredient_map *map;
  for (map = ings; map != NULL; map = map->next)
    {
      if (strcmp (map->ing->name, rcp->method->ing) == 0)
	{
	  gcc_jit_rvalue *var_bowl =
	    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
						 rcp->method->bowl - 1);
	  gcc_jit_rvalue *pop_call =
	    gcc_jit_context_new_call (ctx, NULL, func_pop, 1, &var_bowl);
	  gcc_jit_lvalue *var_value =
	    gcc_jit_rvalue_dereference_field (pop_call, NULL, field_value);
	  gcc_jit_block_add_assignment (block, NULL, map->var,
					gcc_jit_lvalue_as_rvalue (var_value));
	  return;
	}
    }
  error ("undefined ingredient: %s", rcp->method->ing);
}

static void
add_inst_arith (gcc_jit_context *ctx, gcc_jit_block *block,
		enum gcc_jit_binary_op operation)
{
  struct ingredient_map *map;
  for (map = ings; map != NULL; map = map->next)
    {
      if (strcmp (map->ing->name, rcp->method->ing) == 0)
	{
	  gcc_jit_rvalue *var_bowl =
	    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
						 rcp->method->bowl - 1);
	  gcc_jit_rvalue *rvalue_bowls =
	    gcc_jit_lvalue_as_rvalue (var_bowls);
	  gcc_jit_lvalue *target_container =
	    gcc_jit_context_new_array_access (ctx, NULL, rvalue_bowls,
					      var_bowl);
	  gcc_jit_rvalue *rvalue_container =
	    gcc_jit_lvalue_as_rvalue (target_container);
	  gcc_jit_lvalue *var_value =
	    gcc_jit_rvalue_dereference_field (rvalue_container, NULL,
					      field_value);
	  gcc_jit_rvalue *rvalue_value = gcc_jit_lvalue_as_rvalue (var_value);
	  gcc_jit_rvalue *var_ing = gcc_jit_lvalue_as_rvalue (map->var);
	  gcc_jit_rvalue *answer =
	    gcc_jit_context_new_binary_op (ctx, NULL, operation, type_int,
					   rvalue_value, var_ing);
	  gcc_jit_rvalue *push_call_args[3] = {
	    var_bowl,
	    answer,
	    gcc_jit_context_zero (ctx, type_int)
	  };
	  gcc_jit_rvalue *push_call =
	    gcc_jit_context_new_call (ctx, NULL, func_push, 3,
				      push_call_args);
	  gcc_jit_block_add_eval (block, NULL, push_call);
	  return;
	}
    }
  error ("undefined ingredient: %s", rcp->method->ing);
}

static void
add_inst_add_dry (gcc_jit_context *ctx, gcc_jit_block *block)
{
  gcc_jit_rvalue *bowl_id =
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->bowl - 1);
  gcc_jit_block_add_eval (block, NULL,
			  gcc_jit_context_new_call (ctx, NULL, func_add_dry,
						    1, &bowl_id));
}

static void
add_inst_liquefy_ing (void)
{
  struct ingredient_map *map;
  for (map = ings; map != NULL; map = map->next)
    {
      if (strcmp (map->ing->name, rcp->method->ing) == 0)
	{
	  map->ing->type = MEASURE_LIQUID;
	  return;
	}
    }
  error ("undefined ingredient: %s", rcp->method->ing);
}

static void
add_inst_liquefy_bowl (gcc_jit_context *ctx, gcc_jit_block *block)
{
  gcc_jit_rvalue *bowl_id =
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->bowl - 1);
  gcc_jit_block_add_eval (block, NULL,
			  gcc_jit_context_new_call (ctx, NULL, func_liquefy,
						    1, &bowl_id));
}

static void
add_inst_stir (gcc_jit_context *ctx, gcc_jit_block *block)
{
  gcc_jit_rvalue *bowl_id =
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->bowl - 1);
  gcc_jit_rvalue *depth;
  gcc_jit_rvalue *stir_call_args[2];
  if (rcp->method->type == INST_STIR_ING)
    {
      struct ingredient_map *map;
      for (map = ings; map != NULL; map = map->next)
	{
	  if (strcmp (map->ing->name, rcp->method->ing) == 0)
	    {
	      depth = gcc_jit_lvalue_as_rvalue (map->var);
	      goto eval;
	    }
	}
      error ("undefined ingredient: %s", rcp->method->ing);
      return;
    }
  else
    {
      if (rcp->method->time < 1)
	{
	  error ("stir time must be an integer greater than zero");
	  return;
	}
      depth = gcc_jit_context_new_rvalue_from_int (ctx, type_int,
						   rcp->method->time - 1);
    }

 eval:
  stir_call_args[0] = bowl_id;
  stir_call_args[1] = depth;
  gcc_jit_block_add_eval (block, NULL,
			  gcc_jit_context_new_call (ctx, NULL, func_stir,
						    2, stir_call_args));
}

static void
add_inst_mix (gcc_jit_context *ctx, gcc_jit_block *block)
{
  gcc_jit_rvalue *bowl_id =
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->bowl - 1);
  gcc_jit_block_add_eval (block, NULL,
			  gcc_jit_context_new_call (ctx, NULL, func_mix,
						    1, &bowl_id));
}

static void
add_inst_clean (gcc_jit_context *ctx, gcc_jit_block *block)
{
  /* TODO Free all nodes before setting to NULL */
  gcc_jit_rvalue *bowl_id =
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->bowl - 1);
  gcc_jit_lvalue *var_bowl =
    gcc_jit_context_new_array_access (ctx, NULL,
				      gcc_jit_lvalue_as_rvalue (var_bowls),
				      bowl_id);
  gcc_jit_block_add_assignment (block, NULL, var_bowl,
				gcc_jit_context_null (ctx,
						      type_container_ptr));
}

static void
add_inst_pour (gcc_jit_context *ctx, gcc_jit_block *block)
{
  gcc_jit_rvalue *bowl_id =
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->bowl - 1);
  gcc_jit_rvalue *dish_id =
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->dish - 1);
  gcc_jit_rvalue *pour_call_args[2] = {bowl_id, dish_id};
  gcc_jit_rvalue *pour_call =
    gcc_jit_context_new_call (ctx, NULL, func_pour, 2, pour_call_args);
  gcc_jit_block_add_eval (block, NULL, pour_call);
}

static void
add_inst_loop_start (gcc_jit_context *ctx, gcc_jit_block *block)
{
  char *func_name = strlower (rcp->method->verb);
  gcc_jit_function *func;
  gcc_jit_block *block_entry;
  gcc_jit_block *block_main;
  gcc_jit_block *block_done;
  gcc_jit_rvalue *exit_condition;
  struct ingredient_map *map;
  int did_break = 0;
  
  for (map = ings; map != NULL; map = map->next)
    {
      if (strcmp (map->ing->name, rcp->method->ing) == 0)
	{
	  gcc_jit_rvalue *var = gcc_jit_lvalue_as_rvalue (map->var);
	  exit_condition =
	    gcc_jit_context_new_comparison (ctx, NULL, GCC_JIT_COMPARISON_EQ,
					    var,
					    gcc_jit_context_zero (ctx,
								  type_int));
	  goto build;
	}
    }
  error ("undefined ingredient: %s", rcp->method->ing);
  return;

 build:
  if (verbs == NULL)
    verbs = strlist_init (func_name);
  else
    {
      struct strlist *list;
      for (list = verbs; list != NULL; list = list->next)
	{
	  if (strcmp (list->value, func_name) == 0)
	    {
	      error ("reusage of loop identifier: %s", func_name);
	      return;
	    }
	}
      strlist_append (verbs, func_name);
    }
  func = gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_INTERNAL,
				       type_void, func_name, 0, NULL, 0);
  block_entry = gcc_jit_function_new_block (func, "entry");
  block_main = gcc_jit_function_new_block (func, "main");
  block_done = gcc_jit_function_new_block (func, "done");
  gcc_jit_block_end_with_conditional (block_entry, NULL, exit_condition,
				      block_done, block_main);
  for (rcp->method = rcp->method->next; rcp->method != NULL;
       rcp->method = rcp->method->next)
    {
      if (rcp->method->type == INST_LOOP_END)
	{
	  char *end_name = strlower (rcp->method->verb);
	  if (strcmp (func_name, end_name) != 0)
	    {
	      error ("loop end identifier %s does not match start",
		     strbold (end_name));
	      return;
	    }
	  if (rcp->method->ing != NULL)
	    {
	      for (map = ings; map != NULL; map = map->next)
		{
		  if (strcmp (map->ing->name, rcp->method->ing) == 0)
		    {
		      if (did_break)
			goto ret;
		      gcc_jit_block_add_assignment_op
			(block_main, NULL, map->var, GCC_JIT_BINARY_OP_MINUS,
			 gcc_jit_context_one (ctx, type_int));
		      goto ret;
		    }
		}
	      error ("undefined ingredient: %s", rcp->method->ing);
	    }

	ret:
	  if (!did_break)
	    gcc_jit_block_end_with_jump (block_main, NULL, block_entry);
	  break;
	}
      else if (rcp->method->type == INST_LOOP_BREAK)
	{
	  gcc_jit_block_end_with_void_return (block_main, NULL);
	  did_break = 1;
	}
      else if (!did_break)
	add_instruction (ctx, block_main);
    }
  if (rcp->method == NULL)
    {
      error ("unterminated loop");
      exit (1);
    }
  gcc_jit_block_end_with_void_return (block_done, NULL);
  gcc_jit_block_add_eval (block, NULL,
			  gcc_jit_context_new_call (ctx, NULL, func, 0,
						    NULL));
}

static void
add_instruction (gcc_jit_context *ctx, gcc_jit_block *block)
{
  switch (rcp->method->type)
    {
    case INST_TAKE:
      add_inst_take (ctx, block);
      break;
    case INST_PUT:
      add_inst_put (ctx, block);
      break;
    case INST_FOLD:
      add_inst_fold (ctx, block);
      break;
    case INST_ADD:
      add_inst_arith (ctx, block, GCC_JIT_BINARY_OP_PLUS);
      break;
    case INST_REMOVE:
      add_inst_arith (ctx, block, GCC_JIT_BINARY_OP_MINUS);
      break;
    case INST_COMBINE:
      add_inst_arith (ctx, block, GCC_JIT_BINARY_OP_MULT);
      break;
    case INST_DIVIDE:
      add_inst_arith (ctx, block, GCC_JIT_BINARY_OP_DIVIDE);
      break;
    case INST_ADD_DRY:
      add_inst_add_dry (ctx, block);
      break;
    case INST_LIQUEFY_ING:
      add_inst_liquefy_ing ();
      break;
    case INST_LIQUEFY_BOWL:
      add_inst_liquefy_bowl (ctx, block);
      break;
    case INST_STIR_ING:
    case INST_STIR_BOWL:
      add_inst_stir (ctx, block);
      break;
    case INST_MIX:
      add_inst_mix (ctx, block);
      break;
    case INST_CLEAN:
      add_inst_clean (ctx, block);
      break;
    case INST_POUR:
      add_inst_pour (ctx, block);
      break;
    case INST_LOOP_START:
      add_inst_loop_start (ctx, block);
      break;
    }
}

static void
gen_func_main (gcc_jit_context *ctx)
{
  gcc_jit_function *func_main =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_EXPORTED,
				  type_int, "main", 0, NULL, 0);
  gcc_jit_block *block_entry =
    gcc_jit_function_new_block (func_main, "entry");
  gcc_jit_rvalue *null = gcc_jit_context_null (ctx, type_size_t_ptr);
  gcc_jit_rvalue *time_call =
    gcc_jit_context_new_cast (ctx, NULL,
			      gcc_jit_context_new_call (ctx, NULL,
							func_time, 1, &null),
			      type_unsigned);
  int i;
  struct ingredient_map *map;
  
  gcc_jit_block_add_eval (block_entry, NULL,
			  gcc_jit_context_new_call (ctx, NULL, func_srand,
						    1, &time_call));
  for (map = ings; map != NULL; map = map->next)
    {
      gcc_jit_rvalue *var_initval =
	gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					     map->ing->initval);
      gcc_jit_block_add_assignment (block_entry, NULL, map->var, var_initval);
    }

  for (; rcp->method != NULL; rcp->method = rcp->method->next)
    {
      if (rcp->method->type == INST_LOOP_END)
	error ("unmatched loop end instruction");
      else if (rcp->method->type == INST_LOOP_BREAK)
	error ("set instruction not in loop");
      else
	add_instruction (ctx, block_entry);
    }

  for (i = 0; i < rcp->serves; i++)
    {
      gcc_jit_rvalue *var_dish =
	gcc_jit_context_new_rvalue_from_int (ctx, type_int, i);
      gcc_jit_rvalue *print_dish_call =
	gcc_jit_context_new_call (ctx, NULL, func_print_dish, 1, &var_dish);
      gcc_jit_block_add_eval (block_entry, NULL, print_dish_call);
    }
  gcc_jit_block_end_with_return (block_entry, NULL,
				 gcc_jit_context_zero (ctx, type_int));
}

static gcc_jit_context *
generate_context (void)
{
  gcc_jit_context *ctx = gcc_jit_context_acquire ();
  struct ingredient *temp;
  gcc_jit_context_set_int_option (ctx, GCC_JIT_INT_OPTION_OPTIMIZATION_LEVEL,
				  optimization);
  gcc_jit_context_set_bool_option (ctx, GCC_JIT_BOOL_OPTION_DEBUGINFO,
				   debuginfo);
  type_void = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_VOID);
  type_void_ptr = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_VOID_PTR);
  type_int = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_INT);
  type_unsigned = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_UNSIGNED_INT);
  type_size_t = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_SIZE_T);
  type_size_t_ptr = gcc_jit_type_get_pointer (type_size_t);
  type_const_char_ptr =
    gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_CONST_CHAR_PTR);
  gen_prog_start (ctx);
  for (temp = rcp->ings; temp != NULL; temp = temp->next)
    {
      struct ingredient_map *map;
      if (ings == NULL)
        {
	  ings = xmalloc (sizeof (struct ingredient_map));
	  map = ings;
	}
      else
	{
	  map = ings;
	  while (map->next != NULL)
	    map = map->next;
	  map->next = xmalloc (sizeof (struct ingredient_map));
	  map = map->next;
	}
      map->ing = temp;
      map->var = gcc_jit_context_new_global (ctx, NULL,
					     GCC_JIT_GLOBAL_EXPORTED,
					     type_int, temp->name);
    }
  gen_func_main (ctx);
  return ctx;
}

void
compile (char *output)
{
  gcc_jit_context *ctx = generate_context ();
  if (awaiting_exit)
    exit (1);
  switch (last_phase)
    {
    case COMPILE:
      gcc_jit_context_compile_to_file (ctx, GCC_JIT_OUTPUT_KIND_ASSEMBLER,
				       output);
      break;
    case ASSEMBLE:
      gcc_jit_context_compile_to_file (ctx, GCC_JIT_OUTPUT_KIND_OBJECT_FILE,
				       output);
      break;
    case LINK:
      gcc_jit_context_compile_to_file (ctx, GCC_JIT_OUTPUT_KIND_EXECUTABLE,
				       output);
      break;
    }

  gcc_jit_context_dump_to_file (ctx, "/tmp/eccdump.c", 0);
}
