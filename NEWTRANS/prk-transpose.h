#ifndef PRK_TRANSPOSE_H
#define PRK_TRANSPOSE_H

#include "prk-alloc.h" /* ASSALIGN macro */
#include "prk-macros.h"

static inline void prk_transpose_contig(double * restrict b, const double * restrict a, int rowa, int cola, int tilesize)
{
    ASSALIGN(a);
    ASSALIGN(b);
    if (tilesize<=1 || tilesize >= rowa || tilesize >= cola) {
        OMP_PARALLEL_FOR
        for (int i=0; i<rowa; i++) {
            PRAGMA_SIMD
            for (int j=0; j<cola; j++) {
                b[j*rowa+i] = a[i*cola+j];
            }
        }
    } else {
        OMP_PARALLEL
        OMP_FOR_COLLAPSE2
        for (int i=0; i<rowa; i+=tilesize) {
            for (int j=0; j<cola; j+=tilesize) {
                const int imax = (i+tilesize)<rowa ? (i+tilesize) : rowa;
                const int jmax = (j+tilesize)<cola ? (j+tilesize) : cola;
                PRAGMA_SIMD
                for (int jj=j; jj<jmax; jj++) {
                    PRAGMA_SIMD
                    for (int ii=i; ii<imax; ii++) {
                        b[jj*rowa+ii] = a[ii*cola+jj];
                    }
                }
            }
        }
    }
}

static size_t prk_transpose_verify(const double * restrict b, const double * restrict a, int rowa, int cola)
{
    size_t errors = 0;
    for (int i=0; i<rowa; i++) {
        for (int j=0; j<cola; j++) {
            const double diff = b[j*rowa+i] - a[i*cola+j];
            /* -O3 with icc (ICC) 15.0.3 20150408
             * generates incorrect results for this loop,
             * which can be fixed by uncommenting this printf. */
            //printf("diff = %lf\n", diff);
            if (fabs(diff) > 1.e-12) errors++;
        }
    }

    if (errors) {
        printf("there were %zu errors!\n", errors);
        fflush(stdout);
        for (int i=0; i<rowa; i++) {
            for (int j=0; j<cola; j++) {
                const double diff = b[j*rowa+i] - a[i*cola+j];
                printf("(%d,%d) a(i,j)=%40.20lf b(j,i)=%40.20lf %s\n",
                        i,j,a[i*cola+j],b[j*rowa+i],
                        ((fabs(diff) > 1.e-12) ? 1 : 0) ? "WRONG" : "" );
            }
        }
    }
    fflush(stdout);
    return errors;
}

#endif // PRK_TRANSPOSE_H
