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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "errors.h"

int awaiting_exit = 0;

void
error (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  if (isatty (STDERR_FILENO))
    fprintf (stderr, "\033[31;1merror:\033[0m ");
  else
    fprintf (stderr, "error: ");
  vfprintf (stderr, fmt, args);
  va_end (args);
  fputc ('\n', stderr);
  awaiting_exit = 1;
}

void
warning (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  if (isatty (STDERR_FILENO))
    fprintf (stderr, "\033[35;1mwarning:\033[0m ");
  else
    fprintf (stderr, "warning: ");
  vfprintf (stderr, fmt, args);
  va_end (args);
  fputc ('\n', stderr);
}

void
fatal_error (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  if (isatty (STDERR_FILENO))
    fprintf (stderr, "\033[31;1mfatal error:\033[0m ");
  else
    fprintf (stderr, "fatal error: ");
  vfprintf (stderr, fmt, args);
  va_end (args);
  fputc ('\n', stderr);
  abort ();
}
