#ifndef PRK_UTIL_H
#define PRK_UTIL_H

#include <stdlib.h>

#include "prk-alloc.h"

static void prk_fill_seq(double * restrict x, size_t n)
{
    ASSALIGN(x);
    for (size_t i=0; i<n; i++) {
        x[i] = (double)i;
    }
}

static void prk_fill_zero(double * restrict x, size_t n)
{
    ASSALIGN(x);
    for (size_t i=0; i<n; i++) {
        x[i] = 0.0;
    }
}

static void prk_fill_rand(double * restrict x, size_t n)
{
    const double invmax = 1.0/RAND_MAX;
    ASSALIGN(x);
    for (size_t i=0; i<n; i++) {
        x[i] = (double)rand()*invmax;
    }
}

#if defined(_OPENMP)
  #include <omp.h>
#else
  #include <sys/time.h>
#endif

double wtime(void)
{
  double t = 0.0;
#if defined(_OPENMP)
  t = omp_get_wtime();
#else
  struct timeval td; /* seconds since 0 GMT */
  gettimeofday(&td,NULL);
  t  = (double) td.tv_sec + (double) td.tv_usec * 1.e-6;
#endif
  return t;
}
#endif // PRK_UTIL_H
