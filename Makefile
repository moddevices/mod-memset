CC ?= gcc
TARGETS = mod-memset mod-memset-cpu1 mod-memset-cpu2 mod-memset-internal mod-memset-internal-noopt

all: $(TARGETS)

mod-memset: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@

mod-memset-cpu1: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@ -DMOD_MEMSET_CPUSET=1

mod-memset-cpu2: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@ -DMOD_MEMSET_CPUSET=2

mod-memset-internal: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@ -DMOD_MEMSET_INTERNAL

mod-memset-internal-noopt: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@ -DMOD_MEMSET_INTERNAL -DMOD_MEMSET_UNOPTIMIZED

clean:
	rm -f $(TARGETS)
