#include "../../include/hmemory.h"

#include "tcache.h"


static HMALLOC_THREAD_LOCAL t_tcache	t_tcache_storage;
static HMALLOC_THREAD_LOCAL int			t_tcache_init = 0;

t_tcache *tcacheGet(void)
{
	if (!t_tcache_init) {
		ft_memset(&t_tcache_storage, 0, sizeof(t_tcache_storage));
		t_tcache_init = 1;
	}
	return (&t_tcache_storage);
}

void tcacheFlush(t_tcache *tc)
{
	if (!tc)
		return;

	for (int bin = 0; bin < TCACHE_NUM_BINS; bin++) {
		t_tcacheEntry *e = tc->bins[bin];
		while (e) {
			t_tcacheEntry *next = e->next;
			hmallocFreeInternal((void *)e);
			e = next;
		}
		tc->bins[bin]   = NULL;
		tc->counts[bin] = 0;
	}
}
