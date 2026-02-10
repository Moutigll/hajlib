#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../include/libft.h"

#define ITER_SMALL	5
#define ITER_LARGE	3
#define ITER_BIG	1
#define NUM_SIZES	7

#define COLOR_RED	"\x1b[31m"
#define COLOR_GREEN	"\x1b[32m"
#define COLOR_RESET	"\x1b[0m"

typedef struct s_stats
{
	double	mean;
	double	stddev;
	int		iterations;
	long	*times;
}	t_stats;


static size_t	g_buffSizes[NUM_SIZES] = {
	1024,			/* 1 KB */
	10240,			/* 10 KB */
	102400,			/* 100 KB */
	1048576,		/* 1 MB */
	10485760,		/* 10 MB */
	104857600,		/* 100 MB */
	1048576000		/* 1 GB */
};

static long
getTimeNs(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000000000L + ts.tv_nsec);
}

static void
fillBuff(unsigned char *buf, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		buf[i] = (unsigned char)(i % 256);
		i++;
	}
}

static void
calcStats(t_stats *stats)
{
	double	sum = 0;
	double	sumSq = 0;
	int		i;

	i = 0;
	while (i < stats->iterations)
	{
		sum += (double)stats->times[i];
		i++;
	}
	stats->mean = sum / stats->iterations;
	i = 0;
	while (i < stats->iterations)
	{
		sumSq += ((double)stats->times[i] - stats->mean) *
				 ((double)stats->times[i] - stats->mean);
		i++;
	}
	stats->stddev = sqrt(sumSq / stats->iterations);
}

static void
benchmarkCopy(	const char	*name,
				void		*(*copyFunc)(void *, const void *, size_t),
				size_t		size,
				int			iterations,
				t_stats		*stats)
{
	unsigned char	*src;
	unsigned char	*dst;
	int				i;
	long			start;
	long			end;

	stats->iterations = iterations;
	stats->times = malloc(sizeof(long) * iterations);
	if (!stats->times)
		exit(1);

	src = malloc(size);
	dst = malloc(size);
	if (!src || !dst)
		exit(1);

	fillBuff(src, size);

	i = 0;
	while (i < iterations)
	{
		start = getTimeNs();
		copyFunc(dst, src, size);
		end = getTimeNs();
		stats->times[i] = end - start;
		printf("[%s] Iteration %d: %ld ns\n", name, i + 1, stats->times[i]);
		i++;
	}

	calcStats(stats);
	printf("[%s] Size %8zu bytes: mean = %.0f ns, stddev = %.0f ns\n",
		name, size, stats->mean, stats->stddev);

	free(src);
	free(dst);
}

int	main(void)
{
	int		i;
	size_t	size;
	int		iterations;
	t_stats	statsLibc;
	t_stats	statsFt;
	double	gainNs;
	double	gainPercent;

	i = 0;
	while (i < NUM_SIZES)
	{
		size = g_buffSizes[i];
		iterations = (size <= 102400) ? ITER_SMALL
					: (size <= 104857600) ? ITER_LARGE
					: ITER_BIG;

		printf("=== Buffer size: %zu bytes ===\n", size);

		benchmarkCopy("memcpy", memcpy, size, iterations, &statsLibc);
		benchmarkCopy("ft_memcpy", ft_memcpy, size, iterations, &statsFt);

		if (statsLibc.mean < statsFt.mean)
		{
			gainNs = statsFt.mean - statsLibc.mean;
			gainPercent = (gainNs / statsFt.mean) * 100.0;
			printf(COLOR_RED
				"memcpy fastest: %.0f ns vs ft_memcpy: %.0f ns  (+%.0f ns, %.1f%%)\n"
				COLOR_RESET,
				statsLibc.mean, statsFt.mean, gainNs, gainPercent);
		}
		else
		{
			gainNs = statsLibc.mean - statsFt.mean;
			gainPercent = (gainNs / statsLibc.mean) * 100.0;
			printf(COLOR_GREEN
				"ft_memcpy fastest: %.0f ns vs memcpy: %.0f ns  (+%.0f ns, %.1f%%)\n"
				COLOR_RESET,
				statsFt.mean, statsLibc.mean, gainNs, gainPercent);
		}

		printf("\n");
		i++;
	}

	free(statsLibc.times);
	free(statsFt.times);
	return (0);
}
