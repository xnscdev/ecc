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

%{

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libecc/errors.h>
#include <libecc/strutils.h>
#include <libecc/xalloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "chef.h"

extern int yylex (void);
void yyerror (const char *msg);

extern int yylineno;
extern FILE *yyin;
extern struct recipe *main_recipe;

%}

%union {
    char *string;
    int number;
    char *ing;
    struct ingredient *ings;
    struct instruction *inst;
    struct recipe *recipe;
}

%define parse.error detailed
			
%token	<string>	WORD HEADER_INGS HEADER_METHOD DRY_MEASURE
%token	<string>	LIQUID_MEASURE UNDEF_MEASURE REFINED_MEASURE
%token	<string>	COOKING TIME HOURS MINUTES PREHEAT OVEN TO
%token	<string>	DEGREES CELSIUS GAS MARK TAKE FROM REFRIGERATOR
%token	<string>	PUT INTO THE MIXING BOWL FOLD ADD REMOVE
%token	<string>	COMBINE DIVIDE DRY INGREDIENTS LIQUEFY CONTENTS OF
%token	<string>	STIR FOR MIX WELL CLEAN POUR BAKING DISH UNTIL SET
%token	<string>	ASIDE SERVE WITH REFRIGERATE SERVES
%token	<number>	NUMBER ORDER

%type	<string>        word identifier
%type	<ings>		ingredient_list ingredient
%type	<number>	measurement refined_measurement
%type	<number>	bowl_specifier serves_statement
%type	<inst>		instruction inst_take inst_put inst_fold inst_add
%type	<inst>		inst_remove inst_combine inst_divide inst_add_dry
%type	<inst>		inst_liquefy_bowl inst_liquefy_ing inst_stir_bowl
%type	<inst>		inst_stir_ing inst_mix inst_clean inst_pour
%type	<inst>		inst_loop_start inst_loop_end inst_loop_break
%type	<inst>		inst_serve inst_refrigerate method
%type	<recipe>	recipe
			
%start program

%%

program:	recipe { main_recipe = $1; }
	;

recipe:		identifier '.' blank_line comments blank_line ingredient_list
		blank_line extra_attributes method serves_statement spaces
		{
		  $$ = xmalloc (sizeof (struct recipe));
		  $$->name = $1;
		  $$->ings = $6;
		  $$->method = $9;
		  $$->serves = $10;
		}
	;

serves_statement:
		/* empty */ { $$ = 0; }
	|	blank_line SERVES NUMBER '.' { $$ = $3; }
	;

bowl_specifier:	/* empty */ { $$ = 1; }
	|	THE { $$ = 1; }
	|	ORDER { $$ = $1; }
	|	THE ORDER { $$ = $2; }
	;

inst_take:	TAKE identifier FROM REFRIGERATOR '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_TAKE;
		  $$->ing = $2;
		}
	;

inst_put:	PUT identifier INTO bowl_specifier MIXING BOWL '.'
	        {
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_PUT;
		  $$->ing = $2;
		  $$->bowl = $4;
		}
	;

inst_fold:	FOLD identifier INTO bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_FOLD;
		  $$->ing = $2;
		  $$->bowl = $4;
		}
	;

inst_add:	ADD identifier TO bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_ADD;
		  $$->ing = $2;
		  $$->bowl = $4;
		}
	|	ADD identifier '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_ADD;
		  $$->ing = $2;
		  $$->bowl = 1;
		}
	;

inst_remove:	REMOVE identifier FROM bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_REMOVE;
		  $$->ing = $2;
		  $$->bowl = $4;
		}
	|	REMOVE identifier '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_REMOVE;
		  $$->ing = $2;
		  $$->bowl = 1;
		}
	;

inst_combine:	COMBINE identifier INTO bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_COMBINE;
		  $$->ing = $2;
		  $$->bowl = $4;
		}
	|	COMBINE identifier '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_COMBINE;
		  $$->ing = $2;
		  $$->bowl = 1;
		}
	;

inst_divide:	DIVIDE identifier INTO bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_DIVIDE;
		  $$->ing = $2;
		  $$->bowl = $4;
		}
	|	DIVIDE identifier '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_DIVIDE;
		  $$->ing = $2;
		  $$->bowl = 1;
		}
	;

inst_add_dry:	ADD DRY INGREDIENTS TO bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_ADD_DRY;
		  $$->bowl = $5;
		}
	|	ADD DRY INGREDIENTS '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_ADD_DRY;
		  $$->bowl = 1;
		}
	;

inst_liquefy_bowl:
		LIQUEFY CONTENTS OF bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_LIQUEFY_BOWL;
		  $$->bowl = $4;
		}
	;

inst_liquefy_ing:
		LIQUEFY identifier '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_LIQUEFY_ING;
		  $$->ing = $2;
		}
	;

inst_stir_bowl:	STIR bowl_specifier MIXING BOWL FOR NUMBER MINUTES '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_STIR_BOWL;
		  $$->bowl = $2;
		  $$->time = $6;
		}
	;

inst_stir_ing:	STIR identifier INTO bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_STIR_ING;
		  $$->ing = $2;
		  $$->bowl = $4;
		}
	;

inst_mix:	MIX bowl_specifier MIXING BOWL WELL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_MIX;
		  $$->bowl = $2;
		}
	|	MIX WELL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_MIX;
		  $$->bowl = 1;
		}
	;

inst_clean:	CLEAN bowl_specifier MIXING BOWL '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_CLEAN;
		  $$->bowl = $2;
		}
	;

inst_pour:	POUR CONTENTS OF bowl_specifier MIXING BOWL INTO
		bowl_specifier BAKING DISH '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_POUR;
		  $$->bowl = $4;
		  $$->dish = $8;
		}
	;

inst_loop_start:
		word THE identifier '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_LOOP_START;
		  $$->ing = $3;
		  $$->verb = strlower ($1);
		}
	;

inst_loop_end:	word THE identifier UNTIL word '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_LOOP_END;
		  $$->ing = $3;
		  $$->verb = strlower ($1);
		}
	|	word UNTIL word '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_LOOP_END;
		  $$->ing = NULL;
		  $$->verb = strlower ($1);
		}
	;

inst_loop_break:
		SET ASIDE '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_LOOP_BREAK;
		}
	;

inst_serve:	SERVE WITH identifier '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_SERVE;
		  $$->auxname = $3;
		}
	;

inst_refrigerate:
		REFRIGERATE FOR NUMBER HOURS '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_REFRIGERATE;
		  $$->time = $3;
		}
	|	REFRIGERATE '.'
		{
		  $$ = xmalloc (sizeof (struct instruction));
		  $$->type = INST_REFRIGERATE;
		  $$->time = 0;
		}
	;

instruction:	inst_take
	|	inst_put
	|	inst_fold
	|	inst_add
	|	inst_remove
	|	inst_combine
	|	inst_divide
	|	inst_add_dry
	|	inst_liquefy_bowl
	|	inst_liquefy_ing
	|	inst_stir_bowl
	|	inst_stir_ing
	|	inst_mix
	|	inst_clean
	|	inst_pour
	|	inst_loop_start
	|	inst_loop_end
	|	inst_loop_break
	|	inst_serve
	|	inst_refrigerate
	;

method:		HEADER_METHOD '\n' instruction { $$ = $3; }
	|	method optional_newline instruction
		{
		  struct instruction *temp = $1;
		  while (temp->next != NULL)
		    temp = temp->next;
		  temp->next = $3;
		  $3->prev = temp;
		  $$ = $1;
		}
	;

cooking_time:	COOKING TIME ':' NUMBER HOURS '.'
	|	COOKING TIME ':' NUMBER MINUTES '.'
	;

oven_temp:	PREHEAT OVEN TO NUMBER DEGREES CELSIUS '(' GAS MARK NUMBER
		')' '.'
	|	PREHEAT OVEN TO NUMBER DEGREES CELSIUS '.'
	;

extra_attributes:
	        /* empty */
	|	cooking_time blank_line
	|	oven_temp blank_line
	|	cooking_time blank_line oven_temp blank_line
	;

ingredient:	NUMBER measurement identifier
		{
		  $$ = xmalloc (sizeof (struct ingredient));
		  $$->name = $3;
		  $$->initval = $1;
		  $$->type = $2;
		}
	|	NUMBER refined_measurement identifier
		{
		  $$ = xmalloc (sizeof (struct ingredient));
		  $$->name = $3;
		  $$->initval = $1;
		  $$->type = $2;
		}
	|	NUMBER measurement refined_measurement identifier
		{
		  $$ = xmalloc (sizeof (struct ingredient));
		  $$->name = $4;
		  $$->initval = $1;
		  $$->type = $2;
		  if ($$->type == MEASURE_UNDEF)
		    $$->type = $3;
		}
	|	NUMBER identifier
		{
		  $$ = xmalloc (sizeof (struct ingredient));
		  $$->name = $2;
		  $$->initval = $1;
		  $$->type = MEASURE_DRY;
		}
	;

ingredient_list:
	        HEADER_INGS '\n' ingredient { $$ = $3; }
	|	ingredient_list '\n' ingredient
		{
		  struct ingredient *temp = $1;
		  while (temp->next != NULL)
		    temp = temp->next;
		  temp->next = $3;
		  $3->prev = temp;
		  $$ = $1;
		}
	;

refined_measurement:
		REFINED_MEASURE { $$ = MEASURE_DRY; }
	;

measurement:    DRY_MEASURE { $$ = MEASURE_DRY; }
	|	LIQUID_MEASURE { $$ = MEASURE_LIQUID; }
	|	UNDEF_MEASURE { $$ = MEASURE_UNDEF; }
	;

comments:	comment
	|	comments '\n' comment
	;

comment:	comment_word
	|	misc_chars
	|	comment comment_word
	|	comment misc_chars
	;

identifier:	word
	|	identifier word { strmerge ($1, " "); strmerge ($1, $2); }
	;

blank_line:	'\n' '\n'
	|	blank_line '\n'
	;

optional_newline:
		/* empty */
	|	'\n'
	;

spaces:	        optional_newline
	|	blank_line
	;

comment_word:	word
	|	DRY_MEASURE
	|	LIQUID_MEASURE
	|	UNDEF_MEASURE
	|	REFINED_MEASURE
	|	TO
	|	OF
	|	FROM
	|	UNTIL
	|	THE
	|	TAKE
	|	PUT
	|	INTO
	|	FOLD
	|	ADD
	|	REMOVE
	|	COMBINE
	|	DIVIDE
	|	LIQUEFY
	|	STIR
	|	FOR
	|	MIXING
	|	MIX
	|	SERVES
	|	CLEAN
	|	INGREDIENTS
	;

word:		WORD
	|	COOKING
	|	TIME
	|	BAKING
	|	HOURS
	|	MINUTES
	|	OVEN
	|	PREHEAT
	|	GAS
	|	MARK
	|	DEGREES
	|	CELSIUS
	|	DRY
	|	CONTENTS
	|	WELL
	|	POUR
	|	DISH
	|	BOWL
	|	REFRIGERATOR
	|	SET
	|	ASIDE
	|	SERVE
	|	REFRIGERATE
	|	WITH
	;

misc_chars:	'`' | '!' | '@' | '#' | '$' | '%' | '^' | '&' | '*' | '('
	|	')' | '=' | '+' | '[' | '{' | ']' | '}' | '\\' | '|' | ';'
	|	':' | '\'' | '"' | ',' | '<' | '.' | '>' | '/' | '?' | '~'
	;

%%

		void
yyerror (const char *msg)
{
  error ("%d: %s", yylineno, msg);
}
