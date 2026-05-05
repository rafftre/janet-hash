/*
 * SPDX-FileCopyrightText: 2026 Raffaele Tretola <rafftre@hey.com>
 * SPDX-License-Identifier: MPL-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "digest.h"

// Sample usage of the hashing functions in C.

int main(int argc, char *argv[]) {
    (void) argc;

    const unsigned char data[] = "Hello, World!";
    size_t len = sizeof(data) - 1;
    printf("size of data: %lu\n", len);

    digest_algorithm algo;
    if (!digest_parse_algorithm(argv[1], &algo)) {
        fprintf(stderr, "Unknown algorithm: %s\n", argv[1]);
        return 1;
    }

    unsigned char *hash = malloc(algo == DIGEST_SHA1 ? SHA_DIGEST_LENGTH : SHA256_DIGEST_LENGTH);
    if (!hash) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t hash_len = 0;

    if (!digest_compute(data, len, algo, hash, &hash_len)) {
        fprintf(stderr, "Hash computation failed\n");
        free(hash);
        return 1;
    }

    for (size_t i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    free(hash);
    return 0;
}
