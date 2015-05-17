#ifndef PRK_TRANSPOSE_H
#define PRK_TRANSPOSE_H

#include "prk-alloc.h" /* ASSALIGN macro */

static void prk_transpose_contig(double * restrict b, const double * restrict a, size_t rowa, size_t cola, size_t tilesize)
{
    ASSALIGN(a);
    ASSALIGN(b);
    if (tilesize<=1 || tilesize >= rowa || tilesize >= cola) {
        for (size_t i=0; i<rowa; i++) {
            for (size_t j=0; j<cola; j++) {
                b[j*rowa+i] = a[i*cola+j];
            }
        }
    } else {
        for (size_t i=0; i<rowa; i+=tilesize) {
            for (size_t j=0; j<cola; j+=tilesize) {
                const size_t imax = (i+tilesize)<rowa ? (i+tilesize) : rowa;
                const size_t jmax = (j+tilesize)<cola ? (j+tilesize) : cola;
                for (size_t it=i; it<imax; it++) {
                    for (size_t jt=j; jt<jmax; jt++) {
                        b[jt*rowa+it] = a[it*cola+jt];
                    }
                }
            }
        }
    }
}

static size_t prk_transpose_verify(const double * restrict b, const double * restrict a, size_t rowa, size_t cola)
{
    size_t errors = 0;
    for (size_t i=0; i<rowa; i++) {
        for (size_t j=0; j<cola; j++) {
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
        for (size_t i=0; i<rowa; i++) {
            for (size_t j=0; j<cola; j++) {
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
