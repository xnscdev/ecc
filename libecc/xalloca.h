#ifndef _XALLOCA_H
#define _XALLOCA_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

void *xmalloc (size_t size);
void *xcalloc (size_t block, size_t size);
void *xrealloc (void *ptr, size_t size);
char *xstrdup (char *str);

#ifdef __cplusplus
}
#endif

#endif
