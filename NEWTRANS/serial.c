#include <stdio.h>
#include <stdlib.h>

#include "prk-alloc.h"
#include "prk-util.h"

int main(int argc, char * argv[])
{
    size_t dim = (argc>1) ? atol(argv[1]) : 1000;
    double * a = prk_malloc(dim*dim*sizeof(double));
    double * b = prk_malloc(dim*dim*sizeof(double));

    prk_fill_seq(a, dim*dim);
    prk_fill_zero(b, dim*dim);

    prk_free(a);
    prk_free(b);
    return 0;
}
