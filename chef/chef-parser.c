/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 19 "chef-parser.y"


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


#line 95 "chef-parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 266 "chef-parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CHEF_PARSER_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_WORD = 3,                       /* WORD  */
  YYSYMBOL_HEADER_INGS = 4,                /* HEADER_INGS  */
  YYSYMBOL_HEADER_METHOD = 5,              /* HEADER_METHOD  */
  YYSYMBOL_DRY_MEASURE = 6,                /* DRY_MEASURE  */
  YYSYMBOL_LIQUID_MEASURE = 7,             /* LIQUID_MEASURE  */
  YYSYMBOL_UNDEF_MEASURE = 8,              /* UNDEF_MEASURE  */
  YYSYMBOL_REFINED_MEASURE = 9,            /* REFINED_MEASURE  */
  YYSYMBOL_COOKING = 10,                   /* COOKING  */
  YYSYMBOL_TIME = 11,                      /* TIME  */
  YYSYMBOL_HOURS = 12,                     /* HOURS  */
  YYSYMBOL_MINUTES = 13,                   /* MINUTES  */
  YYSYMBOL_PREHEAT = 14,                   /* PREHEAT  */
  YYSYMBOL_OVEN = 15,                      /* OVEN  */
  YYSYMBOL_TO = 16,                        /* TO  */
  YYSYMBOL_DEGREES = 17,                   /* DEGREES  */
  YYSYMBOL_CELSIUS = 18,                   /* CELSIUS  */
  YYSYMBOL_GAS = 19,                       /* GAS  */
  YYSYMBOL_MARK = 20,                      /* MARK  */
  YYSYMBOL_TAKE = 21,                      /* TAKE  */
  YYSYMBOL_FROM = 22,                      /* FROM  */
  YYSYMBOL_REFRIGERATOR = 23,              /* REFRIGERATOR  */
  YYSYMBOL_PUT = 24,                       /* PUT  */
  YYSYMBOL_INTO = 25,                      /* INTO  */
  YYSYMBOL_THE = 26,                       /* THE  */
  YYSYMBOL_MIXING = 27,                    /* MIXING  */
  YYSYMBOL_BOWL = 28,                      /* BOWL  */
  YYSYMBOL_FOLD = 29,                      /* FOLD  */
  YYSYMBOL_ADD = 30,                       /* ADD  */
  YYSYMBOL_REMOVE = 31,                    /* REMOVE  */
  YYSYMBOL_COMBINE = 32,                   /* COMBINE  */
  YYSYMBOL_DIVIDE = 33,                    /* DIVIDE  */
  YYSYMBOL_DRY = 34,                       /* DRY  */
  YYSYMBOL_INGREDIENTS = 35,               /* INGREDIENTS  */
  YYSYMBOL_LIQUEFY = 36,                   /* LIQUEFY  */
  YYSYMBOL_CONTENTS = 37,                  /* CONTENTS  */
  YYSYMBOL_OF = 38,                        /* OF  */
  YYSYMBOL_STIR = 39,                      /* STIR  */
  YYSYMBOL_FOR = 40,                       /* FOR  */
  YYSYMBOL_MIX = 41,                       /* MIX  */
  YYSYMBOL_WELL = 42,                      /* WELL  */
  YYSYMBOL_CLEAN = 43,                     /* CLEAN  */
  YYSYMBOL_POUR = 44,                      /* POUR  */
  YYSYMBOL_BAKING = 45,                    /* BAKING  */
  YYSYMBOL_DISH = 46,                      /* DISH  */
  YYSYMBOL_UNTIL = 47,                     /* UNTIL  */
  YYSYMBOL_SET = 48,                       /* SET  */
  YYSYMBOL_ASIDE = 49,                     /* ASIDE  */
  YYSYMBOL_SERVE = 50,                     /* SERVE  */
  YYSYMBOL_WITH = 51,                      /* WITH  */
  YYSYMBOL_REFRIGERATE = 52,               /* REFRIGERATE  */
  YYSYMBOL_SERVES = 53,                    /* SERVES  */
  YYSYMBOL_NUMBER = 54,                    /* NUMBER  */
  YYSYMBOL_ORDER = 55,                     /* ORDER  */
  YYSYMBOL_56_ = 56,                       /* '.'  */
  YYSYMBOL_57_n_ = 57,                     /* '\n'  */
  YYSYMBOL_58_ = 58,                       /* ':'  */
  YYSYMBOL_59_ = 59,                       /* '('  */
  YYSYMBOL_60_ = 60,                       /* ')'  */
  YYSYMBOL_61_ = 61,                       /* '`'  */
  YYSYMBOL_62_ = 62,                       /* '!'  */
  YYSYMBOL_63_ = 63,                       /* '@'  */
  YYSYMBOL_64_ = 64,                       /* '#'  */
  YYSYMBOL_65_ = 65,                       /* '$'  */
  YYSYMBOL_66_ = 66,                       /* '%'  */
  YYSYMBOL_67_ = 67,                       /* '^'  */
  YYSYMBOL_68_ = 68,                       /* '&'  */
  YYSYMBOL_69_ = 69,                       /* '*'  */
  YYSYMBOL_70_ = 70,                       /* '='  */
  YYSYMBOL_71_ = 71,                       /* '+'  */
  YYSYMBOL_72_ = 72,                       /* '['  */
  YYSYMBOL_73_ = 73,                       /* '{'  */
  YYSYMBOL_74_ = 74,                       /* ']'  */
  YYSYMBOL_75_ = 75,                       /* '}'  */
  YYSYMBOL_76_ = 76,                       /* '\\'  */
  YYSYMBOL_77_ = 77,                       /* '|'  */
  YYSYMBOL_78_ = 78,                       /* ';'  */
  YYSYMBOL_79_ = 79,                       /* '\''  */
  YYSYMBOL_80_ = 80,                       /* '"'  */
  YYSYMBOL_81_ = 81,                       /* ','  */
  YYSYMBOL_82_ = 82,                       /* '<'  */
  YYSYMBOL_83_ = 83,                       /* '>'  */
  YYSYMBOL_84_ = 84,                       /* '/'  */
  YYSYMBOL_85_ = 85,                       /* '?'  */
  YYSYMBOL_86_ = 86,                       /* '~'  */
  YYSYMBOL_YYACCEPT = 87,                  /* $accept  */
  YYSYMBOL_program = 88,                   /* program  */
  YYSYMBOL_recipe = 89,                    /* recipe  */
  YYSYMBOL_serves_statement = 90,          /* serves_statement  */
  YYSYMBOL_bowl_specifier = 91,            /* bowl_specifier  */
  YYSYMBOL_inst_take = 92,                 /* inst_take  */
  YYSYMBOL_inst_put = 93,                  /* inst_put  */
  YYSYMBOL_inst_fold = 94,                 /* inst_fold  */
  YYSYMBOL_inst_add = 95,                  /* inst_add  */
  YYSYMBOL_inst_remove = 96,               /* inst_remove  */
  YYSYMBOL_inst_combine = 97,              /* inst_combine  */
  YYSYMBOL_inst_divide = 98,               /* inst_divide  */
  YYSYMBOL_inst_add_dry = 99,              /* inst_add_dry  */
  YYSYMBOL_inst_liquefy_bowl = 100,        /* inst_liquefy_bowl  */
  YYSYMBOL_inst_liquefy_ing = 101,         /* inst_liquefy_ing  */
  YYSYMBOL_inst_stir_bowl = 102,           /* inst_stir_bowl  */
  YYSYMBOL_inst_stir_ing = 103,            /* inst_stir_ing  */
  YYSYMBOL_inst_mix = 104,                 /* inst_mix  */
  YYSYMBOL_inst_clean = 105,               /* inst_clean  */
  YYSYMBOL_inst_pour = 106,                /* inst_pour  */
  YYSYMBOL_inst_loop_start = 107,          /* inst_loop_start  */
  YYSYMBOL_inst_loop_end = 108,            /* inst_loop_end  */
  YYSYMBOL_inst_loop_break = 109,          /* inst_loop_break  */
  YYSYMBOL_inst_serve = 110,               /* inst_serve  */
  YYSYMBOL_inst_refrigerate = 111,         /* inst_refrigerate  */
  YYSYMBOL_instruction = 112,              /* instruction  */
  YYSYMBOL_method = 113,                   /* method  */
  YYSYMBOL_cooking_time = 114,             /* cooking_time  */
  YYSYMBOL_oven_temp = 115,                /* oven_temp  */
  YYSYMBOL_extra_attributes = 116,         /* extra_attributes  */
  YYSYMBOL_ingredient = 117,               /* ingredient  */
  YYSYMBOL_ingredient_list = 118,          /* ingredient_list  */
  YYSYMBOL_refined_measurement = 119,      /* refined_measurement  */
  YYSYMBOL_measurement = 120,              /* measurement  */
  YYSYMBOL_comments = 121,                 /* comments  */
  YYSYMBOL_comment = 122,                  /* comment  */
  YYSYMBOL_identifier = 123,               /* identifier  */
  YYSYMBOL_blank_line = 124,               /* blank_line  */
  YYSYMBOL_optional_newline = 125,         /* optional_newline  */
  YYSYMBOL_spaces = 126,                   /* spaces  */
  YYSYMBOL_comment_word = 127,             /* comment_word  */
  YYSYMBOL_word = 128,                     /* word  */
  YYSYMBOL_misc_chars = 129                /* misc_chars  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1285

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  171
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  315

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      57,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,    80,    64,    65,    66,    68,    79,
      59,    60,    69,    71,    81,     2,    56,    84,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    78,
      82,    70,    83,    85,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,    76,    74,    67,     2,    61,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    73,    77,    75,    86,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,    83,    95,    96,    99,   100,   101,   102,
     105,   113,   122,   131,   138,   147,   154,   163,   170,   179,
     186,   195,   201,   210,   219,   227,   236,   245,   251,   259,
     267,   278,   287,   294,   304,   311,   320,   326,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   356,   357,
     368,   369,   372,   374,   377,   379,   380,   381,   384,   391,
     398,   407,   417,   418,   430,   433,   434,   435,   438,   439,
     442,   443,   444,   445,   448,   449,   452,   453,   456,   458,
     461,   462,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   519,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   520,   520,   520,   520,   520,   520,   520,   520,
     520,   520,   521,   521,   521,   521,   521,   521,   521,   521,
     521,   521
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "WORD", "HEADER_INGS",
  "HEADER_METHOD", "DRY_MEASURE", "LIQUID_MEASURE", "UNDEF_MEASURE",
  "REFINED_MEASURE", "COOKING", "TIME", "HOURS", "MINUTES", "PREHEAT",
  "OVEN", "TO", "DEGREES", "CELSIUS", "GAS", "MARK", "TAKE", "FROM",
  "REFRIGERATOR", "PUT", "INTO", "THE", "MIXING", "BOWL", "FOLD", "ADD",
  "REMOVE", "COMBINE", "DIVIDE", "DRY", "INGREDIENTS", "LIQUEFY",
  "CONTENTS", "OF", "STIR", "FOR", "MIX", "WELL", "CLEAN", "POUR",
  "BAKING", "DISH", "UNTIL", "SET", "ASIDE", "SERVE", "WITH",
  "REFRIGERATE", "SERVES", "NUMBER", "ORDER", "'.'", "'\\n'", "':'", "'('",
  "')'", "'`'", "'!'", "'@'", "'#'", "'$'", "'%'", "'^'", "'&'", "'*'",
  "'='", "'+'", "'['", "'{'", "']'", "'}'", "'\\\\'", "'|'", "';'",
  "'\\''", "'\"'", "','", "'<'", "'>'", "'/'", "'?'", "'~'", "$accept",
  "program", "recipe", "serves_statement", "bowl_specifier", "inst_take",
  "inst_put", "inst_fold", "inst_add", "inst_remove", "inst_combine",
  "inst_divide", "inst_add_dry", "inst_liquefy_bowl", "inst_liquefy_ing",
  "inst_stir_bowl", "inst_stir_ing", "inst_mix", "inst_clean", "inst_pour",
  "inst_loop_start", "inst_loop_end", "inst_loop_break", "inst_serve",
  "inst_refrigerate", "instruction", "method", "cooking_time", "oven_temp",
  "extra_attributes", "ingredient", "ingredient_list",
  "refined_measurement", "measurement", "comments", "comment",
  "identifier", "blank_line", "optional_newline", "spaces", "comment_word",
  "word", "misc_chars", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,    46,    10,    58,    40,
      41,    96,    33,    64,    35,    36,    37,    94,    38,    42,
      61,    43,    91,   123,    93,   125,    92,   124,    59,    39,
      34,    44,    60,    62,    47,    63,   126
};
#endif

#define YYPACT_NINF (-150)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-5)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1145,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,    24,  -150,   631,  -150,  -150,
     -25,  -150,   -23,   229,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,     0,   397,  -150,  -150,  -150,   313,     1,  -150,  -150,
     397,     3,     7,   -24,   -32,    -3,   881,  -150,  -150,    37,
      38,   -25,   -25,    61,  -150,  -150,  -150,  -150,  1145,   925,
    1145,    13,    59,    -6,    20,    22,     4,  1145,  1145,  1145,
      26,    27,   -25,   831,   -23,    28,   -37,   831,  1145,    50,
      66,    20,  1145,  1145,  1145,  1189,  1145,  1145,  1145,  1233,
     781,    -9,    -8,    47,    39,    36,   -28,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,   -16,    20,
    -150,  -150,    35,  -150,    34,    40,    73,   969,  1013,  1057,
      57,   102,   174,   481,   531,    56,   681,    42,  -150,    68,
    1101,    43,    76,    80,    70,    53,  1145,    69,  -150,  1145,
    1145,    71,  -150,  -150,    -4,   101,    -8,    -8,    -7,    -8,
    -150,    -8,  -150,    -8,  -150,    -8,  -150,    -8,  -150,  -150,
      98,    -8,  -150,   100,   103,    -8,  -150,   731,   117,   581,
      77,  -150,  -150,   113,    78,   108,   110,    -8,  -150,   111,
     114,   115,   116,   118,   109,   128,   121,    84,   129,  -150,
     112,  1145,  -150,  -150,   139,  -150,   142,   143,   145,   146,
     147,   148,   150,   151,   126,   153,   134,  -150,   154,  -150,
     144,   141,   149,   157,   170,   158,   159,   161,   165,   171,
     186,   172,  -150,   176,  -150,   169,  -150,  -150,   175,  -150,
    -150,  -150,  -150,  -150,   177,  -150,    -8,   227,  -150,  -150,
     162,  -150,   160,   228,  -150
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   118,   119,   120,   122,   123,   125,   124,   128,   129,
     126,   127,   136,   135,   130,   131,   132,   133,   121,   134,
     137,   138,   139,   141,   140,     0,     2,     0,    84,     1,
       0,    85,     0,     0,    86,    93,    94,    95,    96,    97,
     102,    99,   103,   104,   101,   113,   105,   106,   107,   108,
     109,   117,   110,    98,   111,   112,   114,   116,   100,   115,
     167,    87,   162,   151,   152,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   163,   164,   165,   166,   168,   169,   170,
     171,     0,    78,    80,    92,    81,     0,     0,    82,    83,
      79,     0,     0,     0,     0,    64,     0,    72,    73,     0,
       0,     0,     0,     0,    75,    76,    77,    74,     0,     0,
      71,     0,     0,    65,    66,     0,    88,    69,     0,    68,
       0,     0,     0,     0,    89,    88,     0,     0,    70,     0,
       0,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     6,     6,   133,   137,   139,   140,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,     0,    91,
      90,     3,     0,    59,     0,     0,     0,     0,     0,     0,
     130,     0,     0,     0,     0,   131,     0,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     0,
       0,     0,    60,    61,     0,     0,     6,     6,     0,     6,
      14,     6,    16,     6,    18,     6,    20,     6,    24,     9,
       0,     6,    28,     0,     0,     6,    34,     0,     0,     0,
       0,     5,    63,     0,     0,     0,     0,     6,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,     0,    31,    33,     0,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,    32,     0,    11,    12,     0,    13,
      15,    17,    19,    23,     0,    26,     6,     0,    21,    25,
       0,    62,     0,     0,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -150,  -150,  -150,  -150,  -149,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,    67,  -150,  -150,    86,  -150,
      99,  -150,   198,  -150,  -150,   222,  -105,   -76,   232,  -150,
     -73,   -27,   -71
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,   135,   199,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   126,   111,   112,   113,
     107,   102,   118,   119,    91,    92,    27,    33,   137,   181,
      93,    28,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      31,   120,   202,   203,    -4,   101,    94,   109,   110,   247,
     209,   110,   207,   127,   129,    97,   182,   197,   197,    98,
      61,    99,   106,   138,    29,    34,   105,    98,   208,    99,
     106,   210,    32,   201,    34,   123,   124,   187,   188,   189,
     191,   192,   193,   194,   196,   200,   198,   198,   121,   248,
     136,    61,   242,   122,    61,   243,   141,    96,    61,   179,
     103,   134,   184,   185,   104,    94,   125,   245,   246,    94,
     249,   130,   250,    94,   251,   131,   252,    61,   253,   133,
     139,   140,   255,   186,   204,   134,   258,   206,   205,   211,
     212,   214,   218,    31,   227,   230,   213,   229,   268,   232,
      31,   237,    31,   233,   239,     1,   178,   234,   235,   236,
     178,    31,     2,     3,     4,     5,     6,     7,   219,     8,
       9,    10,    11,   238,   244,    12,   254,   241,   256,   260,
      13,   257,   264,   263,   265,   266,    14,   267,   269,    15,
     277,   270,   271,   272,    16,   273,    17,    18,    19,   274,
      20,    21,    22,    23,    24,   275,   278,   310,   220,   281,
      31,    31,    31,   276,    31,    31,    31,    31,   279,    31,
     282,   283,   284,    31,   285,   286,   287,     1,   288,   289,
     290,   291,   293,   240,     2,     3,     4,     5,     6,     7,
     292,     8,     9,    10,    11,   295,   221,    12,   298,   304,
     294,   306,    13,   108,   183,   296,   313,   312,    14,   132,
      31,    15,    31,   297,   299,   300,    16,   301,    17,    18,
      19,   302,    20,    21,    22,    23,    24,   303,   305,   307,
     222,   308,     1,   309,   280,    35,    36,    37,    38,     2,
       3,     4,     5,     6,     7,    39,     8,     9,    10,    11,
      40,    41,    12,    42,    43,    44,    45,    13,    46,    47,
      48,    49,    50,    14,    51,    52,    15,    53,    54,    55,
      56,    16,    57,    17,    18,    19,    58,    20,    21,    22,
      23,    24,    59,   311,   314,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     1,   128,   100,    35,
      36,    37,    38,     2,     3,     4,     5,     6,     7,    39,
       8,     9,    10,    11,    40,    41,    12,    42,    43,    44,
      45,    13,    46,    47,    48,    49,    50,    14,    51,    52,
      15,    53,    54,    55,    56,    16,    57,    17,    18,    19,
      58,    20,    21,    22,    23,    24,    59,   180,     0,    60,
      34,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       1,     0,     0,    35,    36,    37,    38,     2,     3,     4,
       5,     6,     7,    39,     8,     9,    10,    11,    40,    41,
      12,    42,    43,    44,    45,    13,    46,    47,    48,    49,
      50,    14,    51,    52,    15,    53,    54,    55,    56,    16,
      57,    17,    18,    19,    58,    20,    21,    22,    23,    24,
      59,     0,     0,    60,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     1,     0,     0,     0,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,   223,     0,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,     0,    20,
      21,    22,    23,    24,     1,     0,     0,   224,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,   225,     0,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,     0,    20,
      21,    22,    23,    24,     1,     0,     0,   226,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,     0,     0,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,   261,    20,
      21,    22,    23,    24,     1,     0,     0,   262,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,     0,     0,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,     0,    20,
      21,    22,    23,    24,     1,     0,     0,    30,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,     0,     0,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,     0,    20,
      21,    22,    23,    24,     1,     0,     0,   228,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,     0,     0,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,     0,    20,
      21,    22,    23,    24,     1,     0,     0,   259,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,     0,   197,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,     0,    20,
      21,    22,    23,    24,     1,     0,   198,     0,     0,     0,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,   142,     0,    12,   143,     0,     0,     0,    13,
     144,   145,   146,   147,   148,    14,     0,   149,    15,     0,
     150,     0,   151,    16,   152,   153,    18,    19,     0,   154,
      21,   155,    23,   156,     1,     0,     0,   114,   115,   116,
     117,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,     0,     0,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,     1,    20,
      21,    22,    23,    24,   117,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,     0,     0,    12,     0,
       0,     0,     0,    13,     0,     0,     0,     0,     0,    14,
       0,     0,    15,     0,     0,     0,     0,    16,     0,    17,
      18,    19,     1,    20,    21,    22,    23,    24,     0,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
       0,   215,    12,     0,     0,     0,     0,    13,     0,     0,
       0,     0,     0,    14,     0,     0,    15,     0,     0,     0,
       0,    16,     0,    17,    18,    19,     1,    20,    21,    22,
      23,    24,     0,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,     0,     0,    12,     0,   216,     0,
       0,    13,     0,     0,     0,     0,     0,    14,     0,     0,
      15,     0,     0,     0,     0,    16,     0,    17,    18,    19,
       1,    20,    21,    22,    23,    24,     0,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,     0,     0,
      12,     0,   217,     0,     0,    13,     0,     0,     0,     0,
       0,    14,     0,     0,    15,     0,     0,     0,     0,    16,
       0,    17,    18,    19,     1,    20,    21,    22,    23,    24,
       0,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,     0,    12,     0,   231,     0,     0,    13,
       0,     0,     0,     0,     0,    14,     0,     0,    15,     0,
       0,     0,     0,    16,     0,    17,    18,    19,     1,    20,
      21,    22,    23,    24,     0,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,     0,     0,    12,     0,
       0,     0,     0,    13,     0,     0,     0,     0,     0,    14,
       0,     0,    15,     0,     0,     0,     0,    16,     0,    17,
      18,    19,     1,    20,    21,    22,    23,    24,     0,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,    11,
       0,     0,    12,     0,     0,     0,     0,    13,     0,     0,
       0,     0,     0,   190,     0,     0,    15,     0,     0,     0,
       0,    16,     0,    17,    18,    19,     1,    20,    21,    22,
      23,    24,     0,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,    11,     0,     0,    12,     0,     0,     0,
       0,    13,     0,     0,     0,     0,     0,    14,     0,     0,
     195,     0,     0,     0,     0,    16,     0,    17,    18,    19,
       0,    20,    21,    22,    23,    24
};

static const yytype_int16 yycheck[] =
{
      27,   106,   151,   152,     0,     4,    33,    10,    14,    16,
      26,    14,    40,   118,   119,    91,    53,    26,    26,    92,
      57,    92,    54,   128,     0,    57,   102,   100,    56,   100,
      54,    47,    57,    42,    57,   111,   112,   142,   143,   144,
     145,   146,   147,   148,   149,   150,    55,    55,    11,    56,
     126,    57,    56,    15,    57,    59,   132,    57,    57,   135,
      57,    57,    12,    13,    57,    92,     5,   216,   217,    96,
     219,    58,   221,   100,   223,    16,   225,    57,   227,    57,
      54,    54,   231,    17,    37,    57,   235,    51,    49,    54,
      56,    18,    35,   120,    38,    27,    56,    55,   247,    56,
     127,   206,   129,    27,   209,     3,   133,    27,    38,    56,
     137,   138,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    54,    23,    23,    28,    56,    28,    12,
      28,    28,    19,    56,    56,    27,    34,    27,    27,    37,
      56,    27,    27,    27,    42,    27,    44,    45,    46,    40,
      48,    49,    50,    51,    52,    27,    27,   306,    56,    20,
     187,   188,   189,    42,   191,   192,   193,   194,    56,   196,
      28,    28,    27,   200,    28,    28,    28,     3,    28,    28,
      54,    28,    28,   210,    10,    11,    12,    13,    14,    15,
      56,    17,    18,    19,    20,    54,    22,    23,    28,    13,
      56,    25,    28,   104,   137,    56,    46,    45,    34,   123,
     237,    37,   239,    56,    56,    56,    42,    56,    44,    45,
      46,    56,    48,    49,    50,    51,    52,    56,    56,    60,
      56,    56,     3,    56,   261,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    56,    56,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,     3,   119,    96,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,   135,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
       3,    -1,    -1,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    -1,    -1,    56,    -1,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    25,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,     3,    -1,    -1,    56,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    25,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,     3,    -1,    -1,    56,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    52,     3,    -1,    -1,    56,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,     3,    -1,    -1,    56,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,     3,    -1,    -1,    56,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,     3,    -1,    -1,    56,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    26,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,     3,    -1,    55,    -1,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    21,    -1,    23,    24,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    -1,
      39,    -1,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,     3,    -1,    -1,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,     3,    48,
      49,    50,    51,    52,     9,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    42,    -1,    44,
      45,    46,     3,    48,    49,    50,    51,    52,    -1,    10,
      11,    12,    13,    14,    15,    -1,    17,    18,    19,    20,
      -1,    22,    23,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    42,    -1,    44,    45,    46,     3,    48,    49,    50,
      51,    52,    -1,    10,    11,    12,    13,    14,    15,    -1,
      17,    18,    19,    20,    -1,    -1,    23,    -1,    25,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    42,    -1,    44,    45,    46,
       3,    48,    49,    50,    51,    52,    -1,    10,    11,    12,
      13,    14,    15,    -1,    17,    18,    19,    20,    -1,    -1,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    42,
      -1,    44,    45,    46,     3,    48,    49,    50,    51,    52,
      -1,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    25,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    42,    -1,    44,    45,    46,     3,    48,
      49,    50,    51,    52,    -1,    10,    11,    12,    13,    14,
      15,    -1,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    42,    -1,    44,
      45,    46,     3,    48,    49,    50,    51,    52,    -1,    10,
      11,    12,    13,    14,    15,    -1,    17,    18,    19,    20,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    42,    -1,    44,    45,    46,     3,    48,    49,    50,
      51,    52,    -1,    10,    11,    12,    13,    14,    15,    -1,
      17,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    42,    -1,    44,    45,    46,
      -1,    48,    49,    50,    51,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    10,    11,    12,    13,    14,    15,    17,    18,
      19,    20,    23,    28,    34,    37,    42,    44,    45,    46,
      48,    49,    50,    51,    52,    88,    89,   123,   128,     0,
      56,   128,    57,   124,    57,     6,     7,     8,     9,    16,
      21,    22,    24,    25,    26,    27,    29,    30,    31,    32,
      33,    35,    36,    38,    39,    40,    41,    43,    47,    53,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,   121,   122,   127,   128,   129,    57,   124,   127,   129,
     122,     4,   118,    57,    57,   124,    54,   117,   117,    10,
      14,   114,   115,   116,     6,     7,     8,     9,   119,   120,
     123,    11,    15,   124,   124,     5,   113,   123,   119,   123,
      58,    16,   115,    57,    57,    90,   124,   125,   123,    54,
      54,   124,    21,    24,    29,    30,    31,    32,    33,    36,
      39,    41,    43,    44,    48,    50,    52,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   128,   124,
     125,   126,    53,   112,    12,    13,    17,   123,   123,   123,
      34,   123,   123,   123,   123,    37,   123,    26,    55,    91,
     123,    42,    91,    91,    37,    49,    51,    40,    56,    26,
      47,    54,    56,    56,    18,    22,    25,    25,    35,    16,
      56,    22,    56,    25,    56,    25,    56,    38,    56,    55,
      27,    25,    56,    27,    27,    38,    56,   123,    54,   123,
     128,    56,    56,    59,    23,    91,    91,    16,    56,    91,
      91,    91,    91,    91,    28,    91,    28,    28,    91,    56,
      12,    47,    56,    56,    19,    56,    27,    27,    91,    27,
      27,    27,    27,    27,    40,    27,    42,    56,    27,    56,
     128,    20,    28,    28,    27,    28,    28,    28,    28,    28,
      54,    28,    56,    28,    56,    54,    56,    56,    28,    56,
      56,    56,    56,    56,    13,    56,    25,    60,    56,    56,
      91,    56,    45,    46,    56
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    89,    90,    90,    91,    91,    91,    91,
      92,    93,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   101,   102,   103,   104,   104,   105,
     106,   107,   108,   108,   109,   110,   111,   111,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   113,
     114,   114,   115,   115,   116,   116,   116,   116,   117,   117,
     117,   117,   118,   118,   119,   120,   120,   120,   121,   121,
     122,   122,   122,   122,   123,   123,   124,   124,   125,   125,
     126,   126,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,    11,     0,     4,     0,     1,     1,     2,
       5,     7,     7,     7,     3,     7,     3,     7,     3,     7,
       3,     8,     4,     7,     3,     8,     7,     6,     3,     5,
      11,     4,     6,     4,     3,     4,     5,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       6,     6,    12,     7,     0,     2,     2,     4,     3,     3,
       4,     2,     3,     3,     1,     1,     1,     1,     1,     3,
       1,     1,     2,     2,     1,     2,     2,     2,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: recipe  */
#line 80 "chef-parser.y"
                       { rcp = (yyvsp[0].recipe); }
#line 2013 "chef-parser.c"
    break;

  case 3: /* recipe: identifier '.' blank_line comments blank_line ingredient_list blank_line extra_attributes method serves_statement spaces  */
#line 85 "chef-parser.y"
                {
		  (yyval.recipe) = xmalloc (sizeof (struct recipe));
		  (yyval.recipe)->name = (yyvsp[-10].string);
		  (yyval.recipe)->ings = (yyvsp[-5].ings);
		  (yyval.recipe)->method = (yyvsp[-2].inst);
		  (yyval.recipe)->serves = (yyvsp[-1].number);
		}
#line 2025 "chef-parser.c"
    break;

  case 4: /* serves_statement: %empty  */
#line 95 "chef-parser.y"
                            { (yyval.number) = 0; }
#line 2031 "chef-parser.c"
    break;

  case 5: /* serves_statement: blank_line SERVES NUMBER '.'  */
#line 96 "chef-parser.y"
                                             { (yyval.number) = (yyvsp[-1].number); }
#line 2037 "chef-parser.c"
    break;

  case 6: /* bowl_specifier: %empty  */
#line 99 "chef-parser.y"
                            { (yyval.number) = 1; }
#line 2043 "chef-parser.c"
    break;

  case 7: /* bowl_specifier: THE  */
#line 100 "chef-parser.y"
                    { (yyval.number) = 1; }
#line 2049 "chef-parser.c"
    break;

  case 8: /* bowl_specifier: ORDER  */
#line 101 "chef-parser.y"
                      { (yyval.number) = (yyvsp[0].number); }
#line 2055 "chef-parser.c"
    break;

  case 9: /* bowl_specifier: THE ORDER  */
#line 102 "chef-parser.y"
                          { (yyval.number) = (yyvsp[0].number); }
#line 2061 "chef-parser.c"
    break;

  case 10: /* inst_take: TAKE identifier FROM REFRIGERATOR '.'  */
#line 106 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_TAKE;
		  (yyval.inst)->ing = (yyvsp[-3].string);
		}
#line 2071 "chef-parser.c"
    break;

  case 11: /* inst_put: PUT identifier INTO bowl_specifier MIXING BOWL '.'  */
#line 114 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_PUT;
		  (yyval.inst)->ing = (yyvsp[-5].string);
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2082 "chef-parser.c"
    break;

  case 12: /* inst_fold: FOLD identifier INTO bowl_specifier MIXING BOWL '.'  */
#line 123 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_FOLD;
		  (yyval.inst)->ing = (yyvsp[-5].string);
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2093 "chef-parser.c"
    break;

  case 13: /* inst_add: ADD identifier TO bowl_specifier MIXING BOWL '.'  */
#line 132 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_ADD;
		  (yyval.inst)->ing = (yyvsp[-5].string);
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2104 "chef-parser.c"
    break;

  case 14: /* inst_add: ADD identifier '.'  */
#line 139 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_ADD;
		  (yyval.inst)->ing = (yyvsp[-1].string);
		  (yyval.inst)->bowl = 1;
		}
#line 2115 "chef-parser.c"
    break;

  case 15: /* inst_remove: REMOVE identifier FROM bowl_specifier MIXING BOWL '.'  */
#line 148 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_REMOVE;
		  (yyval.inst)->ing = (yyvsp[-5].string);
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2126 "chef-parser.c"
    break;

  case 16: /* inst_remove: REMOVE identifier '.'  */
#line 155 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_REMOVE;
		  (yyval.inst)->ing = (yyvsp[-1].string);
		  (yyval.inst)->bowl = 1;
		}
#line 2137 "chef-parser.c"
    break;

  case 17: /* inst_combine: COMBINE identifier INTO bowl_specifier MIXING BOWL '.'  */
#line 164 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_COMBINE;
		  (yyval.inst)->ing = (yyvsp[-5].string);
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2148 "chef-parser.c"
    break;

  case 18: /* inst_combine: COMBINE identifier '.'  */
#line 171 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_COMBINE;
		  (yyval.inst)->ing = (yyvsp[-1].string);
		  (yyval.inst)->bowl = 1;
		}
#line 2159 "chef-parser.c"
    break;

  case 19: /* inst_divide: DIVIDE identifier INTO bowl_specifier MIXING BOWL '.'  */
#line 180 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_DIVIDE;
		  (yyval.inst)->ing = (yyvsp[-5].string);
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2170 "chef-parser.c"
    break;

  case 20: /* inst_divide: DIVIDE identifier '.'  */
#line 187 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_DIVIDE;
		  (yyval.inst)->ing = (yyvsp[-1].string);
		  (yyval.inst)->bowl = 1;
		}
#line 2181 "chef-parser.c"
    break;

  case 21: /* inst_add_dry: ADD DRY INGREDIENTS TO bowl_specifier MIXING BOWL '.'  */
#line 196 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_ADD_DRY;
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2191 "chef-parser.c"
    break;

  case 22: /* inst_add_dry: ADD DRY INGREDIENTS '.'  */
#line 202 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_ADD_DRY;
		  (yyval.inst)->bowl = 1;
		}
#line 2201 "chef-parser.c"
    break;

  case 23: /* inst_liquefy_bowl: LIQUEFY CONTENTS OF bowl_specifier MIXING BOWL '.'  */
#line 211 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_LIQUEFY_BOWL;
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2211 "chef-parser.c"
    break;

  case 24: /* inst_liquefy_ing: LIQUEFY identifier '.'  */
#line 220 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_LIQUEFY_ING;
		  (yyval.inst)->ing = (yyvsp[-1].string);
		}
#line 2221 "chef-parser.c"
    break;

  case 25: /* inst_stir_bowl: STIR bowl_specifier MIXING BOWL FOR NUMBER MINUTES '.'  */
#line 228 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_STIR_BOWL;
		  (yyval.inst)->bowl = (yyvsp[-6].number);
		  (yyval.inst)->time = (yyvsp[-2].number);
		}
#line 2232 "chef-parser.c"
    break;

  case 26: /* inst_stir_ing: STIR identifier INTO bowl_specifier MIXING BOWL '.'  */
#line 237 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_STIR_ING;
		  (yyval.inst)->ing = (yyvsp[-5].string);
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2243 "chef-parser.c"
    break;

  case 27: /* inst_mix: MIX bowl_specifier MIXING BOWL WELL '.'  */
#line 246 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_MIX;
		  (yyval.inst)->bowl = (yyvsp[-4].number);
		}
#line 2253 "chef-parser.c"
    break;

  case 28: /* inst_mix: MIX WELL '.'  */
#line 252 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_MIX;
		  (yyval.inst)->bowl = 1;
		}
#line 2263 "chef-parser.c"
    break;

  case 29: /* inst_clean: CLEAN bowl_specifier MIXING BOWL '.'  */
#line 260 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_CLEAN;
		  (yyval.inst)->bowl = (yyvsp[-3].number);
		}
#line 2273 "chef-parser.c"
    break;

  case 30: /* inst_pour: POUR CONTENTS OF bowl_specifier MIXING BOWL INTO bowl_specifier BAKING DISH '.'  */
#line 269 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_POUR;
		  (yyval.inst)->bowl = (yyvsp[-7].number);
		  (yyval.inst)->dish = (yyvsp[-3].number);
		}
#line 2284 "chef-parser.c"
    break;

  case 31: /* inst_loop_start: word THE identifier '.'  */
#line 279 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_LOOP_START;
		  (yyval.inst)->ing = (yyvsp[-1].string);
		  (yyval.inst)->verb = strlower ((yyvsp[-3].string));
		}
#line 2295 "chef-parser.c"
    break;

  case 32: /* inst_loop_end: word THE identifier UNTIL word '.'  */
#line 288 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_LOOP_END;
		  (yyval.inst)->ing = (yyvsp[-3].string);
		  (yyval.inst)->verb = strlower ((yyvsp[-5].string));
		}
#line 2306 "chef-parser.c"
    break;

  case 33: /* inst_loop_end: word UNTIL word '.'  */
#line 295 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_LOOP_END;
		  (yyval.inst)->ing = NULL;
		  (yyval.inst)->verb = strlower ((yyvsp[-3].string));
		}
#line 2317 "chef-parser.c"
    break;

  case 34: /* inst_loop_break: SET ASIDE '.'  */
#line 305 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_LOOP_BREAK;
		}
#line 2326 "chef-parser.c"
    break;

  case 35: /* inst_serve: SERVE WITH identifier '.'  */
#line 312 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_SERVE;
		  (yyval.inst)->auxname = (yyvsp[-1].string);
		}
#line 2336 "chef-parser.c"
    break;

  case 36: /* inst_refrigerate: REFRIGERATE FOR NUMBER HOURS '.'  */
#line 321 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_REFRIGERATE;
		  (yyval.inst)->time = (yyvsp[-2].number);
		}
#line 2346 "chef-parser.c"
    break;

  case 37: /* inst_refrigerate: REFRIGERATE '.'  */
#line 327 "chef-parser.y"
                {
		  (yyval.inst) = xmalloc (sizeof (struct instruction));
		  (yyval.inst)->type = INST_REFRIGERATE;
		  (yyval.inst)->time = 0;
		}
#line 2356 "chef-parser.c"
    break;

  case 58: /* method: HEADER_METHOD '\n' instruction  */
#line 356 "chef-parser.y"
                                               { (yyval.inst) = (yyvsp[0].inst); }
#line 2362 "chef-parser.c"
    break;

  case 59: /* method: method optional_newline instruction  */
#line 358 "chef-parser.y"
                {
		  struct instruction *temp = (yyvsp[-2].inst);
		  while (temp->next != NULL)
		    temp = temp->next;
		  temp->next = (yyvsp[0].inst);
		  (yyvsp[0].inst)->prev = temp;
		  (yyval.inst) = (yyvsp[-2].inst);
		}
#line 2375 "chef-parser.c"
    break;

  case 68: /* ingredient: NUMBER measurement identifier  */
#line 385 "chef-parser.y"
                {
		  (yyval.ings) = xmalloc (sizeof (struct ingredient));
		  (yyval.ings)->name = (yyvsp[0].string);
		  (yyval.ings)->initval = (yyvsp[-2].number);
		  (yyval.ings)->type = (yyvsp[-1].number);
		}
#line 2386 "chef-parser.c"
    break;

  case 69: /* ingredient: NUMBER refined_measurement identifier  */
#line 392 "chef-parser.y"
                {
		  (yyval.ings) = xmalloc (sizeof (struct ingredient));
		  (yyval.ings)->name = (yyvsp[0].string);
		  (yyval.ings)->initval = (yyvsp[-2].number);
		  (yyval.ings)->type = (yyvsp[-1].number);
		}
#line 2397 "chef-parser.c"
    break;

  case 70: /* ingredient: NUMBER measurement refined_measurement identifier  */
#line 399 "chef-parser.y"
                {
		  (yyval.ings) = xmalloc (sizeof (struct ingredient));
		  (yyval.ings)->name = (yyvsp[0].string);
		  (yyval.ings)->initval = (yyvsp[-3].number);
		  (yyval.ings)->type = (yyvsp[-2].number);
		  if ((yyval.ings)->type == MEASURE_UNDEF)
		    (yyval.ings)->type = (yyvsp[-1].number);
		}
#line 2410 "chef-parser.c"
    break;

  case 71: /* ingredient: NUMBER identifier  */
#line 408 "chef-parser.y"
                {
		  (yyval.ings) = xmalloc (sizeof (struct ingredient));
		  (yyval.ings)->name = (yyvsp[0].string);
		  (yyval.ings)->initval = (yyvsp[-1].number);
		  (yyval.ings)->type = MEASURE_DRY;
		}
#line 2421 "chef-parser.c"
    break;

  case 72: /* ingredient_list: HEADER_INGS '\n' ingredient  */
#line 417 "chef-parser.y"
                                            { (yyval.ings) = (yyvsp[0].ings); }
#line 2427 "chef-parser.c"
    break;

  case 73: /* ingredient_list: ingredient_list '\n' ingredient  */
#line 419 "chef-parser.y"
                {
		  struct ingredient *temp = (yyvsp[-2].ings);
		  while (temp->next != NULL)
		    temp = temp->next;
		  temp->next = (yyvsp[0].ings);
		  (yyvsp[0].ings)->prev = temp;
		  (yyval.ings) = (yyvsp[-2].ings);
		}
#line 2440 "chef-parser.c"
    break;

  case 74: /* refined_measurement: REFINED_MEASURE  */
#line 430 "chef-parser.y"
                                { (yyval.number) = MEASURE_DRY; }
#line 2446 "chef-parser.c"
    break;

  case 75: /* measurement: DRY_MEASURE  */
#line 433 "chef-parser.y"
                            { (yyval.number) = MEASURE_DRY; }
#line 2452 "chef-parser.c"
    break;

  case 76: /* measurement: LIQUID_MEASURE  */
#line 434 "chef-parser.y"
                               { (yyval.number) = MEASURE_LIQUID; }
#line 2458 "chef-parser.c"
    break;

  case 77: /* measurement: UNDEF_MEASURE  */
#line 435 "chef-parser.y"
                              { (yyval.number) = MEASURE_UNDEF; }
#line 2464 "chef-parser.c"
    break;

  case 85: /* identifier: identifier word  */
#line 449 "chef-parser.y"
                                { strmerge ((yyvsp[-1].string), " "); strmerge ((yyvsp[-1].string), (yyvsp[0].string)); }
#line 2470 "chef-parser.c"
    break;


#line 2474 "chef-parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 524 "chef-parser.y"


		void
yyerror (const char *msg)
{
  error ("%d: %s", yylineno, msg);
}
