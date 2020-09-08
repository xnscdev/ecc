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
