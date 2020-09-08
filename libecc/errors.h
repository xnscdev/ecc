#ifndef _ERRORS_H
#define _ERRORS_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int awaiting_exit;

void error (const char *fmt, ...);
void warning (const char *fmt, ...);
void parser_error (const char *fmt, ...);
void parser_warning (const char *fmt, ...);
void fatal_error (const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
