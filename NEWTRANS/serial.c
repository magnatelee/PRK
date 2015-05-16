#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "prk-alloc.h"
#include "prk-util.h"
#include "prk-transpose.h"

int main(int argc, char * argv[])
{
    size_t dim = (argc>1) ? atol(argv[1]) : 10;
    double * a = prk_malloc(dim*dim*sizeof(double));
    double * b = prk_malloc(dim*dim*sizeof(double));

    prk_fill_seq(a, dim*dim);
    prk_fill_zero(b, dim*dim);

    prk_transpose_contig(b, a, dim, dim);

    size_t errors = 0;
    for (size_t i=0; i<dim; i++) {
        for (size_t j=0; j<dim; j++) {
            const double diff = b[j*dim+i] - a[i*dim+j];
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
        for (size_t i=0; i<dim; i++) {
            for (size_t j=0; j<dim; j++) {
                const double diff = b[j*dim+i] - a[i*dim+j];
                printf("(%d,%d) a(i,j)=%40.20lf b(j,i)=%40.20lf %s\n",
                        i,j,a[i*dim+j],b[j*dim+i],
                        ((fabs(diff) > 1.e-12) ? 1 : 0) ? "WRONG" : "" );
            }
        }
    }
    fflush(stdout);

    prk_free(a);
    prk_free(b);
    return 0;
}
