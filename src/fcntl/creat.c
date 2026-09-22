/**
 * @file creat.c
 * @brief Implementation of creat().
 *
 * creat() is a historical function that is equivalent to
 * open(path, O_CREAT | O_WRONLY | O_TRUNC, mode). It has no
 * advantage over open() and is kept only for compatibility.
 */

#include <fcntl.h>

int	creat(const char *path, mode_t mode)
{
	return (open(path, O_CREAT | O_WRONLY | O_TRUNC, mode));
}
