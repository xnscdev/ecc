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
