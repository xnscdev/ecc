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
#include <libecc/xalloca.h>
#include <libgccjit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chef.h"

#define MAX_CONTAINER_COUNT 64

char *srcfile;

static gcc_jit_type *type_void;
static gcc_jit_type *type_void_ptr;
static gcc_jit_type *type_int;
static gcc_jit_type *type_container_ptr;
static gcc_jit_type *type_size_t;
static gcc_jit_field *field_value;
static gcc_jit_field *field_type;
static gcc_jit_field *field_next;
static gcc_jit_function *func_malloc;
static gcc_jit_function *func_push;
static gcc_jit_function *func_pop;
static gcc_jit_lvalue *var_bowls;
static gcc_jit_lvalue *var_dishes;

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
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_INTERNAL,
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
    gcc_jit_context_new_function (ctx, loc, GCC_JIT_FUNCTION_INTERNAL,
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
  func_malloc =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_IMPORTED,
				  type_void_ptr, "malloc", 1, &param_size, 0);
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
}

static void
add_inst_put (gcc_jit_context *ctx, gcc_jit_block *block, struct recipe *rcp)
{
  gcc_jit_rvalue *call_args[3] = {
    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
					 rcp->method->bowl - 1),
    NULL,
    NULL
  };
  gcc_jit_rvalue *push_call;
  struct ingredient *temp;
  for (temp = rcp->ings; temp != NULL; temp = temp->next)
    {
      if (strcmp (temp->name, rcp->method->ing) == 0)
	{
	  call_args[1] =
	    gcc_jit_context_new_rvalue_from_int (ctx, type_int, temp->initval);
	  call_args[2] =
	    gcc_jit_context_new_rvalue_from_int (ctx, type_int,
						 temp->type == MEASURE_LIQUID);
	}
    }
  if (call_args[1] == NULL || call_args[2] == NULL)
    error ("undefined ingredient: %s\n", rcp->method->ing);

  push_call = gcc_jit_context_new_call (ctx, NULL, func_push, 3, call_args);
  gcc_jit_block_add_eval (block, NULL, push_call);
}

static void
gen_func_main (gcc_jit_context *ctx)
{
  gcc_jit_function *func_main =
    gcc_jit_context_new_function (ctx, NULL, GCC_JIT_FUNCTION_EXPORTED,
				  type_int, "main", 0, NULL, 0);
  gcc_jit_lvalue *var_ptr =
    gcc_jit_function_new_local (func_main, NULL, type_container_ptr, "ptr");
  gcc_jit_block *block_entry =
    gcc_jit_function_new_block (func_main, "entry");

  for (; rcp->method != NULL; rcp->method = rcp->method->next)
    {
      switch (rcp->method->type)
	{
	case INST_PUT:
	  add_inst_put (ctx, block_entry, rcp);
	  break;
	}
    }
  gcc_jit_block_end_with_return (block_entry, NULL,
				 gcc_jit_context_zero (ctx, type_int));
}

static gcc_jit_context *
generate_context (struct recipe *recipe)
{
  gcc_jit_context *ctx = gcc_jit_context_acquire ();
  gcc_jit_context_set_int_option (ctx, GCC_JIT_INT_OPTION_OPTIMIZATION_LEVEL,
				  optimization);
  gcc_jit_context_set_bool_option (ctx, GCC_JIT_BOOL_OPTION_DEBUGINFO,
				   debuginfo);
  type_void = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_VOID);
  type_void_ptr = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_VOID_PTR);
  type_int = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_INT);
  type_size_t = gcc_jit_context_get_type (ctx, GCC_JIT_TYPE_SIZE_T);
  gen_prog_start (ctx);
  gen_func_main (ctx);
  return ctx;
}

void
compile (char *output)
{
  gcc_jit_context *ctx = generate_context (rcp);
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
