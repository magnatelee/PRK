#ifndef PRK_UTIL_H
#define PRK_UTIL_H

#include <stdlib.h>

static void prk_fill_seq(double * restrict x, size_t n)
{
    for (size_t i=0; i<n; i++) {
        x[i] = (double)i;
    }
}

static void prk_fill_zero(double * restrict x, size_t n)
{
    for (size_t i=0; i<n; i++) {
        x[i] = 0.0;
    }
}

static void prk_fill_rand(double * restrict x, size_t n)
{
    double invmax = 1.0/RAND_MAX;
    for (size_t i=0; i<n; i++) {
        x[i] = (double)rand()*invmax;
    }
}

#endif // PRK_UTIL_H
