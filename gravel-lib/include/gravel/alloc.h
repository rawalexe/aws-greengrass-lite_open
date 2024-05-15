/* gravel - Utilities for AWS IoT Core clients
 * Copyright (C) 2024 Amazon.com, Inc. or its affiliates
 */

#ifndef GRAVEL_ALLOC_H
#define GRAVEL_ALLOC_H

/*! Generic allocator interface */

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>

/** Allocator vtable. Embedded into allocator structs. */
typedef struct GravelAlloc {
    void *(*const alloc)(
        struct GravelAlloc *ctx, size_t size, size_t alignment
    );
    void (*const free)(struct GravelAlloc *ctx, void *ptr);
} GravelAlloc;

/** Allocate memory from an allocator.
 * Prefer `GRAVEL_ALLOC` or `GRAVEL_ALLOCN`. */
void *gravel_alloc(GravelAlloc *alloc, size_t size, size_t alignment);
/** Free memory allocated from an allocator.
 * Prefer `GRAVEL_AUTOFREE` for scope-bound values. */
void gravel_free(GravelAlloc *alloc, void *ptr);

/** Allocate a `type` from an allocator. */
#define GRAVEL_ALLOC(alloc, type) \
    (type *) gravel_alloc(alloc, sizeof(type), alignof(type))
/** Allocate `n` units of `type` from an allocator. */
#define GRAVEL_ALLOCN(alloc, type, n) \
    (type *) gravel_alloc(alloc, (n) * sizeof(type), alignof(type))

#endif