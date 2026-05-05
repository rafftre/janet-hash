# Native hashing functions to use in Janet

This repo contains a native module for executing SHA-1 and SHA-256
hashing functions on a Janet buffer.


## Build the native library for Janet

```sh
jpm build
```


## Trying

The test folder contains an example that implements some Git functions.
You can run it with
```sh
janet test/git.janet
```

The same example is available as equivalent Clojure code
```sh
clj -M test/git.clj
```

A native sample is also available. Build and run it with
```sh
gcc -Wall -Wextra test/main.c src/digest.c -lcrypto -o build/digest
./build/digest SHA-1
```
