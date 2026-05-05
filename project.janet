# SPDX-FileCopyrightText: 2026 Raffaele Tretola <rafftre@hey.com>
# SPDX-License-Identifier: MPL-2.0

(declare-project :name "hash")

(declare-native
  :name "hash"
  :source @["src/hash.c" "src/digest.c"]
  :lflags @["-lcrypto"])
