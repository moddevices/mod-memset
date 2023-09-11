/* Copied from aarch64 glibc memset

   Copyright (C) 1991-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.
*/

/* allocated memory size used for testing */
#define MOD_MEMSET_SIZE 0x100000 /* 100 MiB */

#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memset */

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  */
#define	op_t	unsigned long int
#define OPSIZ	(sizeof (op_t))

/* Type to use for unaligned operations.  */
typedef unsigned char byte;

#ifdef MOD_MEMSET_UNOPTIMIZED
__attribute__((optimize(0)))
#endif
void* mod_memset(void* dstpp, int c, size_t len)
{
    long int dstp = (long int) dstpp;

    if (len >= 8)
    {
        size_t xlen;
        op_t cccc;

        cccc = (unsigned char) c;
        cccc |= cccc << 8;
        cccc |= cccc << 16;

        if (OPSIZ > 4)
            /* Do the shift in two steps to avoid warning if long has 32 bits.  */
            cccc |= (cccc << 16) << 16;

        /* There are at least some bytes to set.
           No need to test for LEN == 0 in this alignment loop.  */
        while (dstp % OPSIZ != 0)
        {
            ((byte *) dstp)[0] = c;
            dstp += 1;
            len -= 1;
        }

        /* Write 8 `op_t' per iteration until less than 8 `op_t' remain.  */
        xlen = len / (OPSIZ * 8);
        while (xlen > 0)
        {
            ((op_t *) dstp)[0] = cccc;
            ((op_t *) dstp)[1] = cccc;
            ((op_t *) dstp)[2] = cccc;
            ((op_t *) dstp)[3] = cccc;
            ((op_t *) dstp)[4] = cccc;
            ((op_t *) dstp)[5] = cccc;
            ((op_t *) dstp)[6] = cccc;
            ((op_t *) dstp)[7] = cccc;
            dstp += 8 * OPSIZ;
            xlen -= 1;
        }
        len %= OPSIZ * 8;

        /* Write 1 `op_t' per iteration until less than OPSIZ bytes remain.  */
        xlen = len / OPSIZ;
        while (xlen > 0)
        {
            ((op_t *) dstp)[0] = cccc;
            dstp += OPSIZ;
            xlen -= 1;
        }
        len %= OPSIZ;
    }

    /* Write the last few bytes.  */
    while (len > 0)
    {
        ((byte *) dstp)[0] = c;
        dstp += 1;
        len -= 1;
    }

    return dstpp;
}

/* some possible alternatives to memset */
void* mod_memset_alternative_1(void* dstpp, int c, size_t len)
{
    volatile unsigned char *volatile vdstpp = dstpp;

    for (size_t i = 0U; i < len; ++i)
        vdstpp[i] = 0U;

    return dstpp;
}

__attribute__((weak))
void _dummy_symbol_to_prevent_memset_being_optimized_away(void* pnt, size_t len)
{
    (void)pnt;
    (void)len;
}

int main()
{
    void* bigmem = malloc(MOD_MEMSET_SIZE);

    while (1)
    {
       #ifdef MOD_MEMSET_REAL_MEMSET
        memset(bigmem, 0, MOD_MEMSET_SIZE);
        _dummy_symbol_to_prevent_memset_being_optimized_away(bigmem, MOD_MEMSET_SIZE);
       #else
        mod_memset(bigmem, 0, MOD_MEMSET_SIZE);
       #endif
    }

    free(bigmem);
    return 0;
}
