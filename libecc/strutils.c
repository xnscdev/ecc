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

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "strutils.h"
#include "xalloca.h"

struct strlist *
strlist_init (char *value)
{
  struct strlist *list;
  if (value == NULL)
    return NULL;
  list = xmalloc (sizeof (struct strlist));
  list->value = value;
  return list;
}

struct strlist *
strlist_seekbeg (struct strlist *list)
{
  if (list == NULL)
    return NULL;
  while (list->prev != NULL)
    list = list->prev;
  return list;
}

struct strlist *
strlist_seekend (struct strlist *list)
{
  if (list == NULL)
    return NULL;
  while (list->next != NULL)
    list = list->next;
  return list;
}

void
strlist_prepend (struct strlist *list, char *value)
{
  if (list == NULL || value == NULL)
    return;
  list = strlist_seekbeg (list);
  list->prev = strlist_init (value);
  list->prev->next = list;
}

void
strlist_append (struct strlist *list, char *value)
{
  if (list == NULL || value == NULL)
    return;
  list = strlist_seekend (list);
  list->next = strlist_init (value);
  list->next->prev = list;
}

char *
strlower (char *str)
{
  int i;
  for (i = 0; i < strlen (str); i++)
    str[i] = tolower (str[i]);
  return str;
}

char *
strupper (char *str)
{
  int i;
  for (i = 0; i < strlen (str); i++)
    str[i] = toupper (str[i]);
  return str;
}

char *
strbold (const char *str)
{
  char *buffer = xcalloc (sizeof (char), strlen (str) + 9);
  if (isatty (STDERR_FILENO))
    sprintf (buffer, "\033[1m%s\033[0m", str);
  else
    sprintf (buffer, "'%s'", str);
  return buffer;
}

char *
strmerge (char *dest, char *src)
{
  char *temp;
  size_t bufsize = strlen (dest) + strlen (src) + 1;
  temp = xcalloc (sizeof (char), bufsize);
  strcpy (temp, dest);
  strcpy (&temp[strlen (dest)], src);
  memmove (dest, temp, strlen (temp));
  return dest;
}
