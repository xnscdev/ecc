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
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "chef-parser.h"
#include "chef.h"

#define save_string(token) yylval.string = xstrdup (yytext); return token;
#define save_number(token) yylval.number = atoi (yytext); return token;

extern struct strlist *sources;

int yywrap (void);
 
%}

%%

[ \t\v\r]                       ;
\n                              yylineno++; return '\n';
"g"|"kg"|"pinch"|"pinches"      save_string (DRY_MEASURE);
"ml"|"l"|"dash"|"dashes"        save_string (LIQUID_MEASURE);
"cup"|"cups"|"teaspoon"         save_string (UNDEF_MEASURE);
"teaspoons"|"tablespoon"        save_string (UNDEF_MEASURE);
"tablespoons"                   save_string (UNDEF_MEASURE);
"heaped"|"level"                save_string (REFINED_MEASURE);
"Ingredients."                  save_string (HEADER_INGS);
"Method."                       save_string (HEADER_METHOD);
"Cooking"                       save_string (COOKING);
"time"                          save_string (TIME);
"hour"s?                        save_string (HOURS);
"minute"s?                      save_string (MINUTES);
"Pre-heat"                      save_string (PREHEAT);
"oven"                          save_string (OVEN);
"to"                            save_string (TO);
"degrees"                       save_string (DEGREES);
"Celsius"                       save_string (CELSIUS);
"gas"                           save_string (GAS);
"mark"                          save_string (MARK);
"Take"                          save_string (TAKE);
"from"                          save_string (FROM);
"refrigerator"                  save_string (REFRIGERATOR);
"Put"                           save_string (PUT);
"into"                          save_string (INTO);
"the"                           save_string (THE);
"mixing"                        save_string (MIXING);
"bowl"                          save_string (BOWL);
"Fold"                          save_string (FOLD);
"Add"                           save_string (ADD);
"Remove"                        save_string (REMOVE);
"Combine"                       save_string (COMBINE);
"Divide"                        save_string (DIVIDE);
"dry"                           save_string (DRY);
"ingredients"                   save_string (INGREDIENTS);
"Liquefy"|"Liquify"             save_string (LIQUEFY);
"contents"                      save_string (CONTENTS);
"of"                            save_string (OF);
"Stir"                          save_string (STIR);
"for"                           save_string (FOR);
"Mix"                           save_string (MIX);
"well"                          save_string (WELL);
"Clean"                         save_string (CLEAN);
"Pour"                          save_string (POUR);
"baking"                        save_string (BAKING);
"dish"                          save_string (DISH);
"until"                         save_string (UNTIL);
"Set"                           save_string (SET);
"aside"                         save_string (ASIDE);
"Serve"                         save_string (SERVE);
"with"                          save_string (WITH);
"Refrigerate"                   save_string (REFRIGERATE);
"Serves"                        save_string (SERVES);
[a-zA-Z_-]+                     save_string (WORD);
[0-9]+                          save_number (NUMBER);
[0-9]+("st"|"nd"|"rd"|"th")     save_number (ORDER);
.                               return *yytext;

%%

int
yywrap (void)
{
  if (sources == NULL)
    return 1;
  if (strcmp (sources->value, "-") == 0)
    yyin = stdin;
  else
    yyin = fopen (sources->value, "rb");
  if (yyin == NULL)
    {
      error ("failed to open %s: %s", strbold (sources->value),
	     strerror (errno));
      exit (1);
    }
  srcfile = sources->value;
  sources = sources->next;
  return 0;
}
