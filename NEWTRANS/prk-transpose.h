#ifndef PRK_TRANSPOSE_H
#define PRK_TRANSPOSE_H

void prk_transpose_contig(double * restrict b, const double * restrict a, size_t rowa, size_t cola)
{
    for (size_t i=0; i<rowa; i++) {
        for (size_t j=0; j<cola; j++) {
            b[j*rowa+i] = a[i*cola+j];
        }
    }
}

#endif // PRK_TRANSPOSE_H
