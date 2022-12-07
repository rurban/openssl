/*
 * Copyright 1995-2021 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include <errno.h>
#include "bio_local.h"
#include "internal/cryptlib.h"

static int null_write(UNUSED_SHIM(BIO*, b), UNUSED_SHIM(const char*, in), int inl);
static int null_read(UNUSED_SHIM(BIO*, b), UNUSED_SHIM(char*, out),
                     UNUSED_SHIM(int, outl));
static int null_puts(UNUSED_SHIM(BIO*, b), const char *str);
static int null_gets(UNUSED_SHIM(BIO*, b),
                     UNUSED_SHIM(char*, buf),
                     UNUSED_SHIM(int, size));
static long null_ctrl(UNUSED_SHIM(BIO*, b), int cmd, UNUSED_SHIM(long, num),
                      UNUSED_SHIM(void*, ptr));
static const BIO_METHOD null_method = {
    BIO_TYPE_NULL,
    "NULL",
    bwrite_conv,              /* bwrite */
    null_write,               /* bwrite_old */
    bread_conv,               /* bread */
    null_read,                /* bread_old */
    null_puts,
    null_gets,
    null_ctrl,
    NULL,                     /* create */
    NULL,                     /* destroy */
    NULL,                     /* null_callback_ctrl */
    NULL,                     /* bsendmmsg */
    NULL                      /* brecvmmsg */
};

const BIO_METHOD *BIO_s_null(void)
{
    return &null_method;
}

static int null_read(UNUSED_SHIM(BIO*, b), UNUSED_SHIM(char*, out),
                     UNUSED_SHIM(int, outl))
{
    return 0;
}

static int null_write(UNUSED_SHIM(BIO*, b), UNUSED_SHIM(const char*, in), int inl)
{
    return inl;
}

static long null_ctrl(UNUSED_SHIM(BIO*, b), int cmd, UNUSED_SHIM(long, num),
                      UNUSED_SHIM(void*, ptr))
{
    long ret = 1;

    switch (cmd) {
    case BIO_CTRL_RESET:
    case BIO_CTRL_EOF:
    case BIO_CTRL_SET:
    case BIO_CTRL_SET_CLOSE:
    case BIO_CTRL_FLUSH:
    case BIO_CTRL_DUP:
        ret = 1;
        break;
    case BIO_CTRL_GET_CLOSE:
    case BIO_CTRL_INFO:
    case BIO_CTRL_GET:
    case BIO_CTRL_PENDING:
    case BIO_CTRL_WPENDING:
    default:
        ret = 0;
        break;
    }
    return ret;
}

static int null_gets(UNUSED_SHIM(BIO*, b),
                     UNUSED_SHIM(char*, buf),
                     UNUSED_SHIM(int, size))
{
    return 0;
}

static int null_puts(UNUSED_SHIM(BIO*, b), const char *str)
{
    if (str == NULL)
        return 0;
    return strlen(str);
}
