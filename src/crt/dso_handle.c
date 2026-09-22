/**
 * @file dso_handle.c
 * @brief Definition of __dso_handle.
 *
 * __dso_handle is a symbol that GCC/Clang generate references to
 * when compiling code that uses __attribute__((destructor)) or
 * C++ static destructors. It identifies the "current DSO"
 * (dynamic shared object) to __cxa_atexit.
 *
 * In a program without shared libraries, __dso_handle is a dummy
 * symbol that is never dereferenced. It just needs to exist.
 */

/*
 * The symbol is defined here. Its address is used as a unique
 * identifier for the "main program" DSO. We do not care about
 * its value.
 */

#include <bits/crt.h>

void	*__dso_handle = 0;
