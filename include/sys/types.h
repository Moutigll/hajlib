#ifndef _SYS_TYPES_H
# define _SYS_TYPES_H

/**
 * @file sys/types.h
 * @brief POSIX types.
 *
 * This header defines the standard POSIX types in the global
 * namespace: size_t, ssize_t, off_t, mode_t, pid_t, uid_t, gid_t,
 * dev_t, ino_t, nlink_t, blksize_t, blkcnt_t, time_t, and friends.
 *
 * The real typedefs live in <bits/types.h>. This header only
 * aliases them under their POSIX names.
 *
 * These definitions match the kernel ABI per OS, so that direct
 * syscalls with these types pass the correct values.
 */

# include <bits/types.h>

/* --------------------------------------------------------------------------
 * Size-related types
 * -------------------------------------------------------------------------- */

# ifndef __size_t_defined
#  define __size_t_defined
/**
 * @brief Unsigned integer type of the result of the sizeof operator.
 */
typedef __haj_size		size_t;
# endif

# ifndef __ssize_t_defined
#  define __ssize_t_defined
/**
 * @brief Signed integer type, used for sizes and counts.
 *
 * Used by read(), write(), and other functions that return a
 * byte count or -1 on error.
 */
typedef __haj_ssize		ssize_t;
# endif

# ifndef __ptrdiff_t_defined
#  define __ptrdiff_t_defined
/**
 * @brief Signed integer type of the result of subtracting two pointers.
 */
typedef __haj_ptrdiff	ptrdiff_t;
# endif

/* --------------------------------------------------------------------------
 * POSIX types
 * -------------------------------------------------------------------------- */

# ifndef __mode_t_defined
#  define __mode_t_defined
/**
 * @brief File mode (permissions and file type).
 *
 * Used by open(), mkdir(), chmod(), and struct stat.
 */
typedef __haj_mode		mode_t;
# endif

# ifndef __off_t_defined
#  define __off_t_defined
/**
 * @brief File offset.
 *
 * Used by lseek(), mmap(), and struct stat.
 * 64 bits on all modern 64-bit platforms.
 */
typedef __haj_off		off_t;
# endif

# ifndef __pid_t_defined
#  define __pid_t_defined
/**
 * @brief Process ID.
 */
typedef __haj_pid		pid_t;
# endif

# ifndef __uid_t_defined
#  define __uid_t_defined
/**
 * @brief User ID.
 */
typedef __haj_uid		uid_t;
# endif

# ifndef __gid_t_defined
#  define __gid_t_defined
/**
 * @brief Group ID.
 */
typedef __haj_gid		gid_t;
# endif

# ifndef __dev_t_defined
#  define __dev_t_defined
/**
 * @brief Device ID.
 *
 * Used by mknod(), struct stat, and struct dirent.
 */
typedef __haj_dev		dev_t;
# endif

# ifndef __ino_t_defined
#  define __ino_t_defined
/**
 * @brief Inode number.
 *
 * Used by struct stat and struct dirent.
 */
typedef __haj_ino		ino_t;
# endif

# ifndef __nlink_t_defined
#  define __nlink_t_defined
/**
 * @brief Link count.
 *
 * Used by struct stat.
 */
typedef __haj_nlink		nlink_t;
# endif

# ifndef __blksize_t_defined
#  define __blksize_t_defined
/**
 * @brief Block size.
 *
 * Used by struct stat.
 */
typedef __haj_blksize	blksize_t;
# endif

# ifndef __blkcnt_t_defined
#  define __blkcnt_t_defined
/**
 * @brief Block count.
 *
 * Used by struct stat.
 */
typedef __haj_blkcnt	blkcnt_t;
# endif

# ifndef __time_t_defined
#  define __time_t_defined
/**
 * @brief Calendar time in seconds since the Unix epoch.
 *
 * Used by time(), struct stat, struct timespec, struct timeval.
 */
typedef __haj_time		time_t;
# endif

# ifndef __suseconds_t_defined
#  define __suseconds_t_defined
/**
 * @brief Microseconds.
 *
 * Used by struct timeval.
 */
typedef __haj_suseconds	suseconds_t;
# endif

# ifndef __clock_t_defined
#  define __clock_t_defined
/**
 * @brief Clock ticks.
 *
 * Used by clock().
 */
typedef __haj_clock		clock_t;
# endif

# ifndef __clockid_t_defined
#  define __clockid_t_defined
/**
 * @brief Clock ID.
 *
 * Used by clock_gettime(), clock_settime(), etc.
 */
typedef __haj_clockid	clockid_t;
# endif

#endif /* _SYS_TYPES_H */
