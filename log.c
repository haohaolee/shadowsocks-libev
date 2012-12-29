/*
 * $Id: logging.c,v 1.1.1.1 2003/07/03 15:24:54 adminweb Exp $
 */

/*
 * Copyright (c) 2003 The OpenEvidence Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, the following disclaimer,
 *    and the original OpenSSL and SSLeay Licences below. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions, the following disclaimer 
 *    and the original OpenSSL and SSLeay Licences below in
 *    the documentation and/or other materials provided with the
 *    distribution. 
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgments:
 *    "This product includes software developed by the Openevidence Project
 *    for use in the OpenEvidence Toolkit. (http://www.openevidence.org/)"
 *    This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *    This product includes cryptographic software written by Eric Young
 *    (eay@cryptsoft.com).  This product includes software written by Tim
 *    Hudson (tjh@cryptsoft.com)."
 *
 * 4. The names "OpenEvidence Toolkit" and "OpenEvidence Project" must not be
 *    used to endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openevidence-core@openevidence.org.
 *
 * 5. Products derived from this software may not be called "OpenEvidence"
 *    nor may "OpenEvidence" appear in their names without prior written
 *    permission of the OpenEvidence Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgments:
 *    "This product includes software developed by the OpenEvidence Project
 *    for use in the OpenEvidence Toolkit (http://www.openevidence.org/)
 *    This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *    This product includes cryptographic software written by Eric Young
 *    (eay@cryptsoft.com).  This product includes software written by Tim
 *    Hudson (tjh@cryptsoft.com)."
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenEvidence PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenEvidence PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes software developed by the OpenSSL Project
 * for use in the OpenSSL Toolkit (http://www.openssl.org/)
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */

/* 2012-12 modified by haohaolee */

#include <syslog.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "log.h"

static int log_stderr = 0;

int LOG_init(const char *progname)
{
    /* Do not modify log_stderr here! */
    openlog(progname, LOG_PID, LOG_USER);
    return 0;
}

void LOG_exit()
{
    closelog();
}

void LOG_setStderrMode(int v)
{
    /* Make sure that this function works before LOG_init()! */
    log_stderr = v;
}

static void LOG_vsyslog(int priority, const char *format, va_list args)
{
    char buf[16384];
    int need_lf = 0;
    
    vsnprintf(buf, sizeof(buf), format, args);
    syslog(priority, "%s", buf);
    if (log_stderr) {
        if (buf[0] && buf[strlen(buf)-1] != '\n') {
            need_lf = 1;
        }
        fprintf(stderr, "%s%s", buf, need_lf ? "\n" : "");
        fflush(stderr);
    }
}

void LOG_syslog(int priority, const char *format, ...)
{
    va_list args;
    
    va_start(args, format);
    LOG_vsyslog(priority, format, args);
    va_end(args);
}

void LOG_error(const char *format, ...)
{
    va_list args;
    
    va_start(args, format);
    LOG_vsyslog(LOG_ERR, format, args);
    va_end(args);
}

void LOG_warning(const char *format, ...)
{
    va_list args;
    
    va_start(args, format);
    LOG_vsyslog(LOG_WARNING, format, args);
    va_end(args);
}

void LOG_info(const char *format, ...)
{
    va_list args;
    
    va_start(args, format);
    LOG_vsyslog(LOG_INFO, format, args);
    va_end(args);
}

void LOG_debug(const char *format, ...)
{
    va_list args;
    
    va_start(args, format);
    LOG_vsyslog(LOG_DEBUG, format, args);
    va_end(args);
}

