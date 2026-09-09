#include "malloc.h"
#include "../../include/hio.h"

static void	printPtr(void *ptr)
{
	char	hex[17];
	size_t	i;
	size_t	val;

	val = (size_t)ptr;
	i = 0;
	ft_putstr_fd("0x", 1);
	while (i < sizeof(size_t) * 2)
	{
		hex[i] = "0123456789ABCDEF"[(val >> (sizeof(size_t) * 8 - 4)) & 0xF];
		val <<= 4;
		i++;
	}
	hex[i] = '\0';
	ft_putstr_fd(hex, 1);
}

static void	printZone(t_mallocZone *zone, const char *type)
{
	t_mallocBlock	*block;
	void			*start;
	void			*end;

	if (!zone)
		return;

	ft_putstr_fd(type, 1);
	ft_putstr_fd(" : ", 1);
	printPtr(zone);
	ft_putstr_fd("\n", 1);

	while (zone)
	{
		block = zone->blocks;
		while (block)
		{
			if (!block->free)
			{
				start = (void *)(block + 1);
				end = (char *)start + block->size;
				printPtr(start);
				ft_putstr_fd(" - ", 1);
				printPtr(end);
				ft_putstr_fd(" : ", 1);
				ft_putnbr_fd(block->size, 1);
				ft_putstr_fd(" bytes\n", 1);
			}
			block = block->next;
		}
		zone = zone->next;
	}
}

void	show_alloc_mem(void)
{
	ft_putstr_fd("\nTINY : ", 1);
	printZone(g_mallocState.tinyZones, "TINY");

	ft_putstr_fd("SMALL : ", 1);
	printZone(g_mallocState.smallZones, "SMALL");

	ft_putstr_fd("LARGE : ", 1);
	printZone(g_mallocState.largeZones, "LARGE");

	ft_putstr_fd("Total : ", 1);
	ft_putnbr_fd(g_mallocState.totalAlloc - g_mallocState.totalFree, 1);
	ft_putstr_fd(" bytes\n", 1);
}
