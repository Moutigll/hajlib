#ifndef _BITS_TYPES_H
# define _BITS_TYPES_H

# include <bits/os.h>
# include <bits/arch.h>
# include <bits/wordsize.h>

/**
 * @file bits/types.h
 * @brief Internal fixed-width and POSIX-like types.
 *
 * This header defines the real typedefs used across hajlib. The
 * public headers (stddef.h, stdint.h, sys/types.h) alias these
 * into the standard names.
 *
 * Naming convention:
 *   - Internal types use the __haj_ prefix.
 *   - Public types (size_t, mode_t, ...) are defined in their
 *     respective public headers.
 *
 * Do NOT include this header directly from user code. Use the
 * public headers (sys/types.h, stdint.h, ...) instead.
 */

/* --------------------------------------------------------------------------
 * Fixed-width integer types
 * --------------------------------------------------------------------------
 *
 * We could use the compiler's __INT8_TYPE__ and friends, but we
 * define them explicitly for clarity. All modern platforms use
 * two's complement, so signed/unsigned char, short, int, long
 * have the expected sizes.
 */


typedef signed char			__haj_i8;
typedef unsigned char		__haj_u8;

typedef short				__haj_i16;
typedef unsigned short		__haj_u16;

typedef int					__haj_i32;
typedef unsigned int		__haj_u32;

# if __HAJ_SIZEOF_LONG == 8
typedef long				__haj_i64;
typedef unsigned long		__haj_u64;
# elif __HAJ_SIZEOF_LONG_LONG == 8
typedef long long			__haj_i64;
typedef unsigned long long	__haj_u64;
# else
#  error "hajlib: no 64-bit integer type available"
# endif

/*
 * Pointer-sized integer types.
 * intptr_t is signed, uintptr_t is unsigned.
 * Both have the same size as a pointer.
 */
# if __HAJ_SIZEOF_POINTER == 8
typedef __haj_i64			__haj_intptr;
typedef __haj_u64			__haj_uintptr;
# else
typedef __haj_i32			__haj_intptr;
typedef __haj_u32			__haj_uintptr;
# endif

/*
 * Maximum-width integer types.
 * intmax_t and uintmax_t are the widest integer types available.
 */
typedef __haj_i64			__haj_intmax;
typedef __haj_u64			__haj_uintmax;

/* --------------------------------------------------------------------------
 * Size-related types
 * --------------------------------------------------------------------------
 *
 * size_t   : unsigned, result of sizeof
 * ssize_t  : signed, size of a buffer, return of read/write
 * ptrdiff_t: signed, result of pointer subtraction
 *
 * size_t and ptrdiff_t are the same width as a pointer on every
 * modern platform. ssize_t is the signed counterpart of size_t.
 */

# if __HAJ_WORDSIZE == 64
typedef unsigned long		__haj_size;
typedef long				__haj_ssize;
typedef long				__haj_ptrdiff;
# else
typedef unsigned int		__haj_size;
typedef int					__haj_ssize;
typedef int					__haj_ptrdiff;
# endif

/* --------------------------------------------------------------------------
 * POSIX types
 * --------------------------------------------------------------------------
 *
 * These match the kernel ABI per OS. The sizes are chosen to match
 * what the kernel expects when passing these values to syscalls.
 */

/*
 * mode_t: file mode (permissions + file type bits).
 *
 * Linux  : unsigned int (32 bits) on all arches.
 * FreeBSD: unsigned short (16 bits) on most arches.
 * Darwin : unsigned short (16 bits).
 * Windows: not used (no POSIX mode in the kernel ABI).
 *
 * We use the kernel's width so that direct syscalls with a mode_t
 * argument pass the correct value.
 */
# if defined(HAJ_OS_LINUX)
typedef unsigned int		__haj_mode;
# elif defined(HAJ_OS_FREEBSD) || defined(HAJ_OS_DARWIN)
typedef unsigned short		__haj_mode;
# else
typedef unsigned int		__haj_mode;
# endif

/*
 * off_t: file offset, size, and count of bytes.
 *
 * hajlib uses 64 bits everywhere. This is the natural size on
 * all 64-bit platforms and on Darwin. On 32-bit Linux, you must
 * define _FILE_OFFSET_BITS=64 to use the 64-bit lseek syscall
 * (_llseek on some arches). Otherwise, the kernel will interpret
 * the value as 32 bits.
 */
typedef __haj_i64 __haj_off;

/*
 * pid_t: process ID.
 * 32 bits signed on Linux, FreeBSD, Darwin.
 */
typedef int					__haj_pid;

/*
 * uid_t / gid_t: user and group IDs.
 * 32 bits unsigned on Linux, FreeBSD, Darwin.
 */
typedef unsigned int		__haj_uid;
typedef unsigned int		__haj_gid;

/*
 * dev_t: device ID.
 * 64 bits unsigned on modern Linux and FreeBSD.
 * 32 bits signed on Darwin (historical).
 */
# if defined(HAJ_OS_DARWIN)
typedef __haj_i32			__haj_dev;
# else
typedef __haj_u64			__haj_dev;
# endif

/*
 * ino_t: inode number.
 * 64 bits unsigned on modern Linux, FreeBSD, Darwin.
 */
typedef __haj_u64			__haj_ino;

/*
 * nlink_t: link count.
 *
 * Linux/FreeBSD : 64 bits unsigned.
 * Darwin        : 16 bits unsigned.
 *
 * Using the correct width is required for struct stat layout
 * on Darwin. If you never call stat on Darwin, you can use
 * 64 bits everywhere for simplicity.
 */
# if defined(HAJ_OS_DARWIN)
typedef unsigned short __haj_nlink;
# else
typedef __haj_u64 __haj_nlink;
# endif

/*
 * blksize_t: block size.
 * Signed long on all platforms.
 */
typedef long				__haj_blksize;

/*
 * blkcnt_t: block count.
 * 64 bits signed on modern Linux and FreeBSD.
 */
typedef __haj_i64			__haj_blkcnt;

/*
 * time_t: seconds since the Unix epoch.
 * 64 bits signed on all modern 64-bit platforms.
 */
typedef __haj_i64			__haj_time;

/*
 * suseconds_t: microseconds.
 * Signed long on all platforms.
 */
typedef long				__haj_suseconds;

/*
 * clock_t: clock ticks.
 * Signed long on all platforms.
 */
typedef long				__haj_clock;

/*
 * clockid_t: clock ID for clock_gettime.
 * Signed int on all platforms.
 */
typedef int					__haj_clockid;

#endif /* _BITS_TYPES_H */
