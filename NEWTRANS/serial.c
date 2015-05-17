#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "prk-alloc.h"
#include "prk-util.h"
#include "prk-transpose.h"

int main(int argc, char * argv[])
{
    int reps = 10;
    {
        char * tmp = getenv("PRK_REPS");
        if (tmp!=NULL) {
            reps = atoi(tmp);
        }
    }

    size_t dim = (argc>1) ? atol(argv[1]) : 10;
    double * a = prk_malloc(dim*dim*sizeof(double));
    double * b = prk_malloc(dim*dim*sizeof(double));

    size_t tilesize = (argc>2) ? atol(argv[2]) : 32;

    printf("transpose %d x %d matrix, tilesize = %d, reps = %d\n", dim, dim, tilesize, reps);

    prk_fill_seq(a, dim*dim);
    prk_fill_zero(b, dim*dim);

    prk_transpose_contig(b, a, dim, dim, tilesize);

    double t0 = wtime();
    for (int r=0; r<reps; r++) {    
        prk_transpose_contig(b, a, dim, dim, tilesize);
    }
    double t1 = wtime();
    double dt = (t1-t0)/reps;
    double bw = 1.e-9*dim*dim*sizeof(double)/dt;
    printf("%d x %d transpose: dt=%lf s bw=%lf GB/s\n", dim, dim, dt, bw);

    prk_free(a);
    prk_free(b);
    return 0;
}
