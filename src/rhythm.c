
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <bit_array.h>
#include <rhythm.h>


rhythm_t *rhythm_create(bit_index_t nbits) {
    rhythm_t *r = calloc(1, sizeof(rhythm_t));
    // TODO - report failed calloc
    if(nbits)
        r->bits = bit_array_create(nbits);
    return r;
}


void rhythm_rotate(rhythm_t *r, bit_index_t rot) {
    bit_array_cycle_right(r->bits, rot);
}


void rhythm_rotate_next_onset(rhythm_t *r) {
    bit_index_t rot = 0;
    char valid = bit_array_find_next_set_bit(r->bits, 1, &rot);
    if(valid)
        bit_array_cycle_right(r->bits, rot);
}


void rhythm_print(const char *desc, rhythm_t *r) {
    if(r == NULL) {
        printf("ERROR: rhthym_t *ptr = 0x%p == NULL (!!!)\n", (void *)r);
        return;
    }
    if(r->bits == NULL) {
        printf("ERROR: BIT_ARRAY *(r->bits) = NULL (!!!)\n");
    }
    printf("%s", desc);
    for(int ix=0; ix<r->bits->num_of_bits; ix++) {
        printf("%c", 
            bit_array_get_bit(r->bits, ix) ?
            'X' : '.'
        );
    }
    printf("\n");
}


/*
    Below rhythm creation functions are adapted from source code for the book
    Creating Rhythms by Stefan Hollos and Richard Hollos
*/


/*
 *                            COPYRIGHT
 *
 *  cfcv_usage and cvcf              from cfcv.c
 *  chsequl_usage and chsequl        from chsequl.c
 *  oddeven, pfold_usage, and pfold  from  pfold.c
 * 
 *  Copyright (C) 2014 Exstrom Laboratories LLC
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  A copy of the GNU General Public License is available on the internet at:
 *  http://www.gnu.org/copyleft/gpl.html
 *
 *  or you can write to:
 *
 *  The Free Software Foundation, Inc.
 *  675 Mass Ave
 *  Cambridge, MA 02139, USA
 *
 *  Exstrom Laboratories LLC contact:
 *  stefan(AT)exstrom.com
 *
 *  Exstrom Laboratories LLC
 *  Longmont, CO 80503, USA
 *
 */

void cfcv_usage(void) {
    printf("usage: cfcv(n, a_arr)\n");
    printf("  Calculates a continued fraction convergent\n");
    printf("  n     = number of terms\n");
    printf("  a_arr = simple continued fraction term\n");

}
void cfcv(unsigned int nterm, unsigned long *a_arr, unsigned long *out) {
    unsigned int i;
    unsigned long a, p0, p1, p2, q0, q1, q2;

    p0 = 0;
    p1 = 1;
    q0 = 1;
    q1 = 0;

    for(i=0; i<nterm; ++i) {
        a = a_arr[i];
        p2 = a*p1 + p0;
        q2 = a*q1 + q0;
        p0 = p1;
        p1 = p2;
        q0 = q1;
        q1 = q2;
    }

    out[0] = p2;
    out[1] = q2;
}


void chsequl_usage(void) {
    printf("usage: chsequl(upper_bool, n, k, z)\n");
    printf("  Generates the upper or lower Christoffel word for p/q\n");
    printf("  upper_bool = type of word\n");
    printf("    1 = upper\n");
    printf("    0 = lower\n");
    printf("  n = number of pattern 'pulses'\n");
    printf("  k = number of pattern 'onsets'\n");
    printf("  p = numerator (derived from k)\n");
    printf("  q = denominator (derived from n-k\n");
    printf("  z = number of terms to generate, default=n\n");
}
BIT_ARRAY * chsequl(uint8_t upper, unsigned long n, unsigned long k, unsigned long z) {
    unsigned long p = k;   // num_onsets
    unsigned long q = n-k; // num_rests
    unsigned long a = p;
    unsigned long b = q;
    unsigned long i = 0;
    BIT_ARRAY *ba;

    // update n according to 'optional' var z, number of terms
    n = (z>0) ? z : p+q;

    ba = bit_array_create(n);
    do{
        // printf(argv[1][0]=='u' ? "1" : "0");
        if(upper)
            bit_array_set_bit(ba, i);
        else
            bit_array_clear_bit(ba, i);
        ++i;

        for(a=p, b=q; a!=b && i<n; ++i) {
            if(a>b){
                // printf("1");
                bit_array_set_bit(ba, i);
                b+=q;
            }
            else{
                // printf("0");
                bit_array_clear_bit(ba, i);
                a+=p;
            }
        }
        if(a==b && i<n){
            // printf(argv[1][0]=='u' ? "0" : "1");
            if(upper)
                bit_array_clear_bit(ba, i);
            else
                bit_array_set_bit(ba, i);
            ++i;
        }
    } while(i<n);

    // printf("\n");
    return ba;
}

// oddeven finds a and b such that n = 2^a * (2*b+1)
void oddeven( unsigned int n, unsigned int *a, unsigned int *b) {
    unsigned int k,l;

    // two's complement of n = -n or ~n + 1
    l = n & -n;  // this is 2^a
    *b = (n / l - 1)/2;
    for(k=0; l>1; ++k) l>>=1;
    *a = k;
    return;
}
void pfold_usage() {
    printf("usage: pfold(n, m, f)\n");
    printf("  Generates fold sequences.\n");
    printf("  n = number of terms, 1,3,7,15,31,63,127,...\n");
    printf("  m = number of bits\n");
    printf("  f = function number 0 -> 2^m-1\n");
}
BIT_ARRAY * pfold(unsigned int n, unsigned int m, unsigned int f) {
    unsigned int i, j, k;
    unsigned int b;
    BIT_ARRAY *ba = bit_array_create(n);
    for(i=1; i<=n; ++i) {
        oddeven(i, &k, &j);
        k = k % m;
        b =  f & (1 << k) ? 1 : 0;
        if((2*j+1) % 4 > 1) b = 1 - b;
        // printf("%u", b);

        if(b)
            bit_array_set_bit(ba, i-1);
        else
            bit_array_clear_bit(ba, i-1);
    }
    return ba;
}

