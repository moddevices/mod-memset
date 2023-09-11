
#include <stddef.h> /* for size_t */

/* some possible alternatives to memset */
void* memset_alternative_1(void* dstpp, int c, size_t len)
{
    volatile unsigned char *volatile vdstpp = dstpp;

    for (size_t i = 0U; i < len; ++i)
        vdstpp[i] = 0U;

    return dstpp;
}
