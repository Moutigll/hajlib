/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file mman.h
 * @brief POSIX memory mapping functions and constants.
 * @Created: 2026/09/26 04:37:44 by Moutig
 * @Updated: 2026/09/26 04:40:41 by Moutig
 *
 * Declares mmap, munmap, mprotect, msync, madvise, mlock, and
 * munlock. Constants are defined per OS in <bits/mman.h>.
 */

#ifndef _SYS_MMAN_H
# define _SYS_MMAN_H

# include <bits/compiler.h>
# include <bits/mman.h>
# include <sys/types.h>

# ifdef __cplusplus
extern "C" {
# endif

/* ----- mmap / munmap ----- */

/**
 * @brief Map files or devices into memory, or allocate anonymous memory.
 *
 * @param addr   Hint address (ignored unless MAP_FIXED).
 * @param len    Length of the mapping in bytes.
 * @param prot   Protection flags (PROT_*).
 * @param flags  Mapping flags (MAP_*).
 * @param fd     File descriptor (-1 for anonymous mapping).
 * @param offset Offset in the file (must be page-aligned).
 * @return Pointer to the mapped area, or MAP_FAILED on error.
 */
void	*mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);

/**
 * @brief Unmap a previously mapped region.
 *
 * @param addr Start of the region (must be page-aligned).
 * @param len  Length of the region.
 * @return 0 on success, -1 on error.
 */
int		munmap(void *addr, size_t len);


/* ----- Protection ----- */

/**
 * @brief Change the protection of a mapped region.
 *
 * @param addr Start of the region.
 * @param len  Length of the region.
 * @param prot New protection flags.
 * @return 0 on success, -1 on error.
 */
int		mprotect(void *addr, size_t len, int prot);


/* ----- Sync ----- */

/**
 * @brief Synchronize a mapped file with its backing store.
 *
 * @param addr  Start of the region.
 * @param len   Length of the region.
 * @param flags MS_ASYNC, MS_SYNC, or MS_INVALIDATE.
 * @return 0 on success, -1 on error.
 */
int		msync(void *addr, size_t len, int flags);


/* ----- Advice ----- */

/**
 * @brief Give advice about the expected usage of a mapped region.
 *
 * @param addr   Start of the region.
 * @param len    Length of the region.
 * @param advice MADV_* advice.
 * @return 0 on success, -1 on error.
 */
int		madvise(void *addr, size_t len, int advice);


/* ----- Locking ----- */

/**
 * @brief Lock a region in memory (prevent swapping).
 *
 * @param addr Start of the region.
 * @param len  Length of the region.
 * @return 0 on success, -1 on error.
 */
int		mlock(const void *addr, size_t len);

/**
 * @brief Unlock a region in memory.
 *
 * @param addr Start of the region.
 * @param len  Length of the region.
 * @return 0 on success, -1 on error.
 */
int		munlock(const void *addr, size_t len);

/**
 * @brief Lock all memory of the process in RAM.
 *
 * @param flags MCL_CURRENT, MCL_FUTURE, or MCL_ONFAULT.
 * @return 0 on success, -1 on error.
 */
int		mlockall(int flags);

/**
 * @brief Unlock all memory of the process.
 *
 * @return 0 on success, -1 on error.
 */
int		munlockall(void);

/* ----- Convenience macros ----- */

# ifndef MAP_FAILED
#  define MAP_FAILED ((void *)-1)
# endif

# ifdef __cplusplus
}
# endif

#endif /* _SYS_MMAN_H */
