#pragma once

#include <stdarg.h>

int     LOG_init (const char *progname);

void    LOG_exit ();

void    LOG_setStderrMode (int v);
void    LOG_syslog (int priority, const char *format,...);

void    LOG_error (const char *format,...);

void    LOG_warning (const char *format,...);

void    LOG_info (const char *format,...);

void    LOG_debug (const char *format,...);

