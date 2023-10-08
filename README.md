# libmtrandom
Shared library that replaces C rand/srand with std::mt19937 implementation.

This version is designed for UNIX-like systems - if no `srand()` was called,
it fetches the seed from `/dev/urandom`, using POSIX API to read it.

The Makefile is somewhat hacky because of -fno-pic. It yields a neat result
that is both small and well optimized, but might fail for some compilers.

Builds shared object that links to libc and libgcc_s, but libstdc++ part
is included statically.

Tested on GCC 11 (Ubuntu 22.04).

# Build

`Makefile` might be helpful. If it's not, just compile `libmtrandom.cpp`
as a shared library.

# Usage

Run a program that uses rand/srand with `LD_PRELOAD=libmtrandom.so`.
