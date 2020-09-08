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
