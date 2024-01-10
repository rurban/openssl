/*
 * Copyright 1995-2021 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include "internal/cryptlib.h"
#include <openssl/evp.h>
#include <openssl/objects.h>
#include "crypto/evp.h"

static int null_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                         const unsigned char *iv, int enc);
static int null_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                       const unsigned char *in, size_t inl);
static const EVP_CIPHER n_cipher = {
    NID_undef,
    1, 0, 0, 0,
    EVP_ORIG_GLOBAL,
    null_init_key,
    null_cipher,
    NULL,       /* cleanup */
    0,          /* ctx_size */
    NULL,       /* set_asn1_parameters */
    NULL,       /* get_asn1_parameters */
    NULL,       /* ctrl */
    NULL,       /* app_data */
    0,          /* name_id */
    NULL,       /* type_name */
    NULL,       /* description */
    NULL,       /* prov */
    {0},        /* refcnt */
    NULL,       /* newctx */
    NULL,       /* einit */
    NULL,       /* dinit */
    NULL,       /* cupdate */
    NULL,       /* cfinal */
    NULL,       /* ccipher */
    NULL,       /* freectx */
    NULL,       /* dupctx */
    NULL,       /* get_params */
    NULL,       /* get_ctx_params */
    NULL,       /* set_ctx_params */
    NULL,       /* gettable_params */
    NULL,       /* gettable_ctx_params */
    NULL        /* settable_ctx_params */
};

const EVP_CIPHER *EVP_enc_null(void)
{
    return &n_cipher;
}

static int null_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                         const unsigned char *iv, int enc)
{
    (void)ctx;
    (void)key;
    (void)iv;
    (void)enc;
    return 1;
}

static int null_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                       const unsigned char *in, size_t inl)
{
    (void)ctx;
    if (in != out)
        memcpy(out, in, inl);
    return 1;
}
