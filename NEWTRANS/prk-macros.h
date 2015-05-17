#ifndef PRK_MACROS_H
#define PRK_MACROS_H

#if (( __STDC_VERSION__ >= 199901L ) || (__cplusplus >= 201103L ))

#define PRAGMA(x) _Pragma(#x)

/******************* OpenMP *******************/
#if defined(_OPENMP)

#define OMP_PARALLEL PRAGMA(omp parallel)
#define OMP_PARALLEL_FOR PRAGMA(omp parallel for schedule(static))
#define OMP_FOR PRAGMA(omp for schedule(static))

#define OMP_PARALLEL_FOR_COLLAPSE(n) PRAGMA(omp parallel for collapse(n) schedule(static))
#define OMP_PARALLEL_FOR_COLLAPSE2 OMP_PARALLEL_FOR_COLLAPSE(2)
#define OMP_PARALLEL_FOR_COLLAPSE3 OMP_PARALLEL_FOR_COLLAPSE(3)
#define OMP_PARALLEL_FOR_COLLAPSE4 OMP_PARALLEL_FOR_COLLAPSE(4)

#define OMP_PARALLEL_FOR_REDUCE_ADD(r) PRAGMA(omp parallel for reduction (+ : r) schedule(static))

#define PRAGMA_SIMD  PRAGMA(omp simd)

#endif /* OpenMP */
/**********************************************/

#if defined(__INTEL_COMPILER) && !defined(_OPENMP)
#define PRAGMA_SIMD  PRAGMA(simd)
#endif /* Intel compiler */

#else /* C99 _Pragma */

#warning Compiler does not understand C99-style _Pragma.

/******************* OpenMP *******************/
#define OMP_PARALLEL
#define OMP_PARALLEL_FOR
#define OMP_FOR
#define OMP_PARALLEL_FOR_COLLAPSE(n)
#define OMP_PARALLEL_FOR_COLLAPSE2
#define OMP_PARALLEL_FOR_COLLAPSE3
#define OMP_PARALLEL_FOR_COLLAPSE4
#define OMP_PARALLEL_FOR_REDUCE_ADD(r)
/**********************************************/

#define PRAGMA_SIMD

#endif /* C99 _Pragma */

#endif // PRK_MACROS_H
