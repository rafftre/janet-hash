/*
 * SPDX-FileCopyrightText: 2026 Raffaele Tretola <rafftre@hey.com>
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef HASH_DIGEST_H
#define HASH_DIGEST_H

#include <stddef.h>

// Supported hashing algorithms
typedef enum {
    DIGEST_SHA1,
    DIGEST_SHA256
} digest_algorithm;

// Parses an hashing algorithm from the provided string
int digest_parse_algorithm(const char *name, digest_algorithm *algo);

// Calculates the hash of data using the specified algorithm.
// Caller provides buffer 'out_hash' with at least expected digest bytes.
// Note: 'data' is treated as raw bytes, not a null-terminated string.
int digest_compute(const unsigned char *data, size_t len,
                 digest_algorithm algo,
                 unsigned char *out_hash,
                 size_t *out_len);

#endif
