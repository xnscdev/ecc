/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_CHEF_PARSER_H_INCLUDED
# define YY_YY_CHEF_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    WORD = 258,                    /* WORD  */
    HEADER_INGS = 259,             /* HEADER_INGS  */
    HEADER_METHOD = 260,           /* HEADER_METHOD  */
    DRY_MEASURE = 261,             /* DRY_MEASURE  */
    LIQUID_MEASURE = 262,          /* LIQUID_MEASURE  */
    UNDEF_MEASURE = 263,           /* UNDEF_MEASURE  */
    REFINED_MEASURE = 264,         /* REFINED_MEASURE  */
    COOKING = 265,                 /* COOKING  */
    TIME = 266,                    /* TIME  */
    HOURS = 267,                   /* HOURS  */
    MINUTES = 268,                 /* MINUTES  */
    PREHEAT = 269,                 /* PREHEAT  */
    OVEN = 270,                    /* OVEN  */
    TO = 271,                      /* TO  */
    DEGREES = 272,                 /* DEGREES  */
    CELSIUS = 273,                 /* CELSIUS  */
    GAS = 274,                     /* GAS  */
    MARK = 275,                    /* MARK  */
    TAKE = 276,                    /* TAKE  */
    FROM = 277,                    /* FROM  */
    REFRIGERATOR = 278,            /* REFRIGERATOR  */
    PUT = 279,                     /* PUT  */
    INTO = 280,                    /* INTO  */
    THE = 281,                     /* THE  */
    MIXING = 282,                  /* MIXING  */
    BOWL = 283,                    /* BOWL  */
    FOLD = 284,                    /* FOLD  */
    ADD = 285,                     /* ADD  */
    REMOVE = 286,                  /* REMOVE  */
    COMBINE = 287,                 /* COMBINE  */
    DIVIDE = 288,                  /* DIVIDE  */
    DRY = 289,                     /* DRY  */
    INGREDIENTS = 290,             /* INGREDIENTS  */
    LIQUEFY = 291,                 /* LIQUEFY  */
    CONTENTS = 292,                /* CONTENTS  */
    OF = 293,                      /* OF  */
    STIR = 294,                    /* STIR  */
    FOR = 295,                     /* FOR  */
    MIX = 296,                     /* MIX  */
    WELL = 297,                    /* WELL  */
    CLEAN = 298,                   /* CLEAN  */
    POUR = 299,                    /* POUR  */
    BAKING = 300,                  /* BAKING  */
    DISH = 301,                    /* DISH  */
    UNTIL = 302,                   /* UNTIL  */
    SET = 303,                     /* SET  */
    ASIDE = 304,                   /* ASIDE  */
    SERVE = 305,                   /* SERVE  */
    WITH = 306,                    /* WITH  */
    REFRIGERATE = 307,             /* REFRIGERATE  */
    SERVES = 308,                  /* SERVES  */
    NUMBER = 309,                  /* NUMBER  */
    ORDER = 310                    /* ORDER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define WORD 258
#define HEADER_INGS 259
#define HEADER_METHOD 260
#define DRY_MEASURE 261
#define LIQUID_MEASURE 262
#define UNDEF_MEASURE 263
#define REFINED_MEASURE 264
#define COOKING 265
#define TIME 266
#define HOURS 267
#define MINUTES 268
#define PREHEAT 269
#define OVEN 270
#define TO 271
#define DEGREES 272
#define CELSIUS 273
#define GAS 274
#define MARK 275
#define TAKE 276
#define FROM 277
#define REFRIGERATOR 278
#define PUT 279
#define INTO 280
#define THE 281
#define MIXING 282
#define BOWL 283
#define FOLD 284
#define ADD 285
#define REMOVE 286
#define COMBINE 287
#define DIVIDE 288
#define DRY 289
#define INGREDIENTS 290
#define LIQUEFY 291
#define CONTENTS 292
#define OF 293
#define STIR 294
#define FOR 295
#define MIX 296
#define WELL 297
#define CLEAN 298
#define POUR 299
#define BAKING 300
#define DISH 301
#define UNTIL 302
#define SET 303
#define ASIDE 304
#define SERVE 305
#define WITH 306
#define REFRIGERATE 307
#define SERVES 308
#define NUMBER 309
#define ORDER 310

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 43 "chef-parser.y"

    char *string;
    int number;
    char *ing;
    struct ingredient *ings;
    struct instruction *inst;
    struct recipe *recipe;

#line 185 "chef-parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CHEF_PARSER_H_INCLUDED  */
