;;; SPDX-FileCopyrightText: 2026 Raffaele Tretola <rafftre@hey.com>
;;; SPDX-License-Identifier: MPL-2.0

(defn make-object
  "Returns a sequence of bytes for the header and the content of the object."
  [type_tag content]
  (let [type_bytes    (map byte type_tag)
        content_bytes (map byte content)
        space_byte    32]
    (concat type_bytes [space_byte (count content) 0] content_bytes)))

(defn hash-object
  "Returns the hash computed with the specified algorithm on the content.
   The supported algorithms are MD5, SHA-1, and SHA-256."
  [algorithm content]
  (let [md (java.security.MessageDigest/getInstance algorithm)]
    (.update md (byte-array content))
    (.digest md)))

(defn bytes->hex
  "Format bytes as hexadecimal string"
  [bytes]
  (apply str
         (map #(format "%02x" (bit-and 0xFF %)) bytes)))

(->> "sample content"
    (make-object "blob")
    (hash-object "SHA-1")
    (bytes->hex)
    (println))
