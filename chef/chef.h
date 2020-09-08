#ifndef _CHEF_H
#define _CHEF_H

enum
  {
    COMPILE = 4,
    ASSEMBLE,
    LINK
  };

enum
  {
    MEASURE_DRY = 128,
    MEASURE_LIQUID,
    MEASURE_UNDEF
  };

enum
  {
    INST_TAKE = 64,
    INST_PUT,
    INST_FOLD,
    INST_ADD,
    INST_ADD_DRY,
    INST_REMOVE,
    INST_COMBINE,
    INST_DIVIDE,
    INST_LIQUEFY_BOWL,
    INST_LIQUEFY_ING,
    INST_STIR_BOWL,
    INST_STIR_ING,
    INST_MIX,
    INST_CLEAN,
    INST_POUR,
    INST_LOOP_START,
    INST_LOOP_END,
    INST_LOOP_BREAK,
    INST_SERVE,
    INST_REFRIGERATE
  };

struct ingredient
{
  char *name;
  int initval;
  int type;
  struct ingredient *prev;
  struct ingredient *next;
};

struct instruction
{
  int type;
  char *ing;
  int bowl;
  int dish;
  int time;
  char *verb;
  char *auxname;
  struct instruction *prev;
  struct instruction *next;
};

struct recipe
{
  char *name;
  struct ingredient *ings;
  struct instruction *method;
  int serves;
  struct recipe *prev;
  struct recipe *next;
};

#endif
