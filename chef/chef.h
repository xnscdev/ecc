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

extern int optimization;
extern int debuginfo;
extern int last_phase;
extern struct recipe *rcp;
extern char *srcfile;

void compile (char *output);

#endif
