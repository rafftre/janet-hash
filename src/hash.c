/*
 * SPDX-FileCopyrightText: 2026 Raffaele Tretola <rafftre@hey.com>
 * SPDX-License-Identifier: MPL-2.0
 */

#include <janet.h>
#include <openssl/sha.h>
#include "digest.h"

static Janet cfun_hash_calc(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);

    const char *salg = janet_getcstring(argv, 0);
    digest_algorithm algo;
    if (!digest_parse_algorithm(salg, &algo)) {
        janet_panicf("Unknown algorithm: %v\n", argv[0]);
    }

    const JanetBuffer *content = janet_getbuffer(argv, 1);

    JanetBuffer *result = janet_buffer(algo == DIGEST_SHA1 ? SHA_DIGEST_LENGTH : SHA256_DIGEST_LENGTH);

    size_t hash_len = 0;
    if (!digest_compute(content->data, content->count, algo, result->data, &hash_len)) {
        janet_panic("Hash computation failed\n");
    }

    result->count = hash_len;
    return janet_wrap_buffer(result);
}

static JanetReg hash_cfuns[] = {
    {"calc", cfun_hash_calc, "(hash/calc alg data)\n\nCompute the hash of data using the provided algorithm\n(one of 'SHA-1' or 'SHA-256')"},
    {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "hash", hash_cfuns);
}
