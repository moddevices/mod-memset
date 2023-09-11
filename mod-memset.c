
/* allocated memory size used for testing */
#define MOD_MEMSET_SIZE 0x100000 /* 100 MiB */

#include <stdlib.h> /* for malloc */

#ifdef MOD_MEMSET_INTERNAL_MEMSET
#include "glibc-memset.c"
#else
#include <string.h>
#endif

__attribute__((weak))
void _dummy_symbol_to_prevent_memset_being_optimized_away(void* ptr, size_t len)
{
    (void)ptr;
    (void)len;
}

int main()
{
    void* bigmem = malloc(MOD_MEMSET_SIZE);

    while (1)
    {
        memset(bigmem, 0, MOD_MEMSET_SIZE);
        _dummy_symbol_to_prevent_memset_being_optimized_away(bigmem, MOD_MEMSET_SIZE);
    }

    free(bigmem);
    return 0;
}
