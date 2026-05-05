# SPDX-FileCopyrightText: 2026 Raffaele Tretola <rafftre@hey.com>
# SPDX-License-Identifier: MPL-2.0

(import /build/hash :as hash)

(defn make-object [type content]
  "Returns a buffer of bytes for the header and the content of the object."
  (-> @""
    (buffer/push-string type)
    (buffer/push-byte 32)
    (buffer/push-byte (length content))
    (buffer/push-byte 0)
    (buffer/push-string content)))

(defn hash-object
  "Returns the hash computed with the specified algorithm on the content.
   The supported algorithms are SHA-1 and SHA-256."
  [algorithm content]
  (hash/calc algorithm content))

(defn buffer->hex
  "Format buffer as hexadecimal string"
  [buffer]
  (apply string
         (map |(string/format "%02x" $) buffer)))

(->> "sample content"
    (make-object "blob")
    (hash-object "SHA-1")
    (buffer->hex)
    (print))
