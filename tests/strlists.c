#include <libecc/strutils.h>
#include <libecc/xalloca.h>
#include <assert.h>
#include <gc.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ELEMENTS 1000

int
main (void)
{
  struct strlist *list = strlist_init ("Start");
  struct strlist *temp;
  int i;

  GC_init ();
  for (i = 0; i < NUM_ELEMENTS; i++)
    {
      int len = snprintf (NULL, 0, "%d", i);
      char *buffer = xcalloc (sizeof (char), len + 1);
      sprintf (buffer, "%d", i);
      strlist_append (list, buffer);
    };

  temp = strlist_seekbeg (list);
  if (temp != list)
    exit (1);

  for (i = -1; temp != NULL; temp = temp->next, i++)
    ;

  assert (i == NUM_ELEMENTS);
  return 0;
}
