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
#include <gc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chef.h"

#define OPT_VERSION 0x200

extern int yywrap (void);
extern int yyparse (void);

int optimization;
int debuginfo;
int last_phase;
struct strlist *sources;
struct recipe *rcp;

static struct
{
  char *flag;
  char *desc;
} options[] = {
  {"-O#", "Optimize generated code"},
  {"-S", "Compile only, don't assemble or link"},
  {"-c", "Compile and assemble only, don't link"},
  {"-g", "Generate debugging information"},
  {"-h, --help", "Show this help text and exit"},
  {"-o FILE, --output=FILE", "Write compilation output to FILE"},
  {"--version", "Show the version of this program and exit"}
};

static void
usage (void)
{
  int i;
  printf ("Usage: chef [OPTIONS] [FILES]...\nOptions:\n");
  for (i = 0; i < sizeof options / sizeof options[0]; i++)
    printf (" %-36s%s\n", options[i].flag, options[i].desc);
}

static void
version (void)
{
  printf ("chef (ECC) " PACKAGE_VERSION "\n");
}

int
main (int argc, char **argv)
{
  struct strlist *flags = NULL;
  char *outfile = NULL;
  int i;
  
  GC_init ();
  optimization = 0;
  last_phase = LINK;
  debuginfo = 0;
  sources = NULL;
  for (i = 1; i < argc; i++)
    {
      if (flags == NULL)
	flags = strlist_init (argv[i]);
      else
	strlist_append (flags, argv[i]);
    }

  for (; flags != NULL; flags = flags->next)
    {
      char *flag = flags->value;
      if (strncmp (flag, "-O", 2) == 0)
	{
	  if (strlen (flag) < 3)
	    optimization = 1;
	  else
	    {
	      char *endptr;
	      flag += 2;
	      optimization = strtol (flag, &endptr, 10);
	      if (*endptr != '\0' || optimization < 0 || optimization > 3)
		error ("invalid optimization level %s", strbold (flag));
	    }
	}
      else if (strcmp (flag, "-S") == 0)
	last_phase = COMPILE;
      else if (strcmp (flag, "-c") == 0)
	last_phase = ASSEMBLE;
      else if (strcmp (flag, "-g") == 0)
	debuginfo = 1;
      else if (strcmp (flag, "-h") == 0 || strcmp (flag, "--help") == 0)
	{
	  usage ();
	  exit (0);
	}
      else if (strcmp (flag, "-o") == 0)
	{
	  if (flags->next == NULL)
	    error ("option %s requires an argument", strbold ("-o"));
	  else
	    {
	      flags = flags->next;
	      outfile = flags->value;
	    }
	}
      else if (strncmp (flag, "--output=", 9) == 0)
	{
	  char *option = flags->value + 9;
	  if (*option == '\0')
	    error ("option %s requires an argument", strbold ("--output"));
	  else
	    outfile = option;
	}
      else if (strcmp (flag, "--output") == 0)
	error ("option %s requires an argument", strbold ("--output"));
      else if (strcmp (flag, "--version") == 0)
	{
	  version ();
	  exit (0);
	}
      else if (*flag == '-')
	warning ("ignoring unrecognized command-line option %s",
		 strbold (flag));
      else
	{
	  if (sources == NULL)
	    sources = strlist_init (flag);
	  else
	    strlist_append (sources, flag);
	}
    }
  if (awaiting_exit)
    exit (1);

  if (sources == NULL)
    {
      error ("no input files");
      exit (1);
    }
  if (outfile == NULL)
    outfile = "a.out";

  yywrap ();
  yyparse ();
  if (awaiting_exit)
    exit (1);
  compile (outfile);
  return 0;
}
