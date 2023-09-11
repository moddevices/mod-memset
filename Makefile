CC ?= gcc
TARGETS = mod-memset mod-memset-internal mod-memset-internal-noopt

all: $(TARGETS)

mod-memset: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@

mod-memset-internal: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@ -DMOD_MEMSET_INTERNAL_MEMSET

mod-memset-internal-noopt: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@ -DMOD_MEMSET_INTERNAL_MEMSET -DMOD_MEMSET_UNOPTIMIZED

clean:
	rm -f $(TARGETS)
