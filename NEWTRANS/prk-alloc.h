#ifndef PRK_ALLOC_H
#define PRK_ALLOC_H

#include <stdlib.h>

#define ALIGNMENT 64

static void * prk_malloc(size_t bytes)
{
    void * ptr = NULL;
    int rc = posix_memalign(&ptr, ALIGNMENT, bytes);
    if (rc) abort();
    return ptr;
}

static void prk_free(void * ptr)
{
    free(ptr);
}

#endif // PRK_ALLOC_H
