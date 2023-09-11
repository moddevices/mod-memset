CC ?= gcc
TARGETS = mod-memset mod-memset-noopt

all: $(TARGETS)

mod-memset: mod-memset.c
	$(CC) $< -std=gnu99 -O3 -Wall -o $@

mod-memset-noopt: mod-memset.c
	$(CC) $< -std=gnu99 -O3 -Wall -o $@ -DMOD_MEMSET_UNOPTIMIZED

clean:
	rm -f $(TARGETS)
