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

#include <gc.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "xalloca.h"

void *
xmalloc (size_t size)
{
  void *buffer = GC_malloc (size);
  if (buffer == NULL)
    fatal_error ("memory allocation failure -- please report a bug!");
  return buffer;
}

void *
xcalloc (size_t block, size_t size)
{
  void *buffer = xmalloc (block * size);
  memset (buffer, 0, block * size);
  return buffer;
}

void *
xrealloc (void *ptr, size_t size)
{
  void *buffer = GC_realloc (ptr, size);
  if (buffer == NULL)
    fatal_error ("memory allocation failure -- please report a bug!");
  return buffer;
}

char *
xstrdup (char *str)
{
  char *buffer = GC_strdup (str);
  if (buffer == NULL)
    fatal_error ("memory allocation failure -- please report a bug!");
  return buffer;
}
