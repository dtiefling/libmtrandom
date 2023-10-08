# libmtrandom
Shared library that replaces C rand/srand with std::mt19937 implementation.

The Makefile is somewhat hacky because of -fno-pic. It yields a neat result
that is both small and well optimized, but might fail for some compilers.

Builds shared object that links to libc and libgcc_s, but libstdc++ part
is included statically.

Tested on GCC 11 (Ubuntu 22.04).
