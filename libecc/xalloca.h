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

#ifndef _XALLOCA_H
#define _XALLOCA_H

#include <stddef.h>

void *xmalloc (size_t size);
void *xcalloc (size_t block, size_t size);
void *xrealloc (void *ptr, size_t size);
char *xstrdup (char *str);

#endif
