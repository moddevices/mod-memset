CC ?= gcc
TARGETS = mod-memset mod-memset-noopt mod-memset-realmemset

all: $(TARGETS)

mod-memset: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@

mod-memset-noopt: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@ -DMOD_MEMSET_UNOPTIMIZED

mod-memset-realmemset: mod-memset.c
	$(CC) $< -std=gnu11 -O3 -Wall -o $@ -DMOD_MEMSET_REAL_MEMSET

clean:
	rm -f $(TARGETS)
