#ifndef PRK_ALLOC_H
#define PRK_ALLOC_H

#include <stdlib.h>

#define ALIGNMENT 64

#ifdef __INTEL_COMPILER
#define ASSALIGN(a) __assume_aligned((a), ALIGNMENT)
#else
#define ASSALIGN(a)
#endif

static void * prk_malloc(size_t bytes)
{
    void * ptr = NULL;
    int rc = posix_memalign(&ptr, ALIGNMENT, bytes);
    if (rc!=0 || ptr==NULL) abort();
    return ptr;
}

static void prk_free(void * ptr)
{
    free(ptr);
}

#endif // PRK_ALLOC_H
