/*
 * SPDX-FileCopyrightText: 2026 Raffaele Tretola <rafftre@hey.com>
 * SPDX-License-Identifier: MPL-2.0
 */

#include <strings.h>
#include <openssl/sha.h>
#include "digest.h"

static int hash_sha1(const unsigned char *data, size_t len, unsigned char *out_hash) {
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, data, len);
    SHA1_Final(out_hash, &ctx);
    return 1;
}

static int hash_sha256(const unsigned char *data, size_t len, unsigned char *out_hash) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, data, len);
    SHA256_Final(out_hash, &ctx);
    return 1;
}

int digest_compute(const unsigned char *data, size_t len,
                 digest_algorithm algo,
                 unsigned char *out_hash,
                 size_t *out_len) {

    if (!data || !out_hash || !out_len) {
        return 0;
    }

    switch (algo) {
        case DIGEST_SHA1:
            *out_len = SHA_DIGEST_LENGTH;
            return hash_sha1(data, len, out_hash);

        case DIGEST_SHA256:
            *out_len = SHA256_DIGEST_LENGTH;
            return hash_sha256(data, len, out_hash);

        default:
            return 0;
    }
}

int digest_parse_algorithm(const char *name, digest_algorithm *algo) {
    if (!name || !algo) {
        return 0;
    }

    if (strcasecmp(name, "SHA-1") == 0) {
        *algo = DIGEST_SHA1;
        return 1;
    }

    if (strcasecmp(name, "SHA-256") == 0) {
        *algo = DIGEST_SHA256;
        return 1;
    }

    return 0;
}
