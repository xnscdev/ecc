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

#ifndef _STRUTILS_H
#define _STRUTILS_H

struct strlist
{
  char *value;
  struct strlist *prev;
  struct strlist *next;
};

struct strlist *strlist_init (char *value);
struct strlist *strlist_seekbeg (struct strlist *list);
struct strlist *strlist_seekend (struct strlist *list);
void strlist_prepend (struct strlist *list, char *value);
void strlist_append (struct strlist *list, char *value);
char *strlower (char *str);
char *strupper (char *str);
char *strbold (const char *str);
char *strmerge (char *dest, char *src);

#endif
