#ifndef TISS_VECTOR_H
#define TISS_VECTOR_H

#include <tiss/sys.h>

typedef struct ts__vector ts__vector_t;
typedef struct ts__vector *ts__vector_ptr;

typedef int (*ts__vector_transform_cb)(ts__vector_ptr self, size_t index,
                                       void *item);

struct ts_vector;

// construction and destruction
int ts__vector_init(ts__vector_t **self, size_t item_size);
int ts__vector_reserve(ts__vector_t *self, size_t capacity);
void ts__vector_free(ts__vector_t **self);

// data manipulation
ssize_t ts__vector_push(ts__vector_ptr self, const void *item);
ssize_t ts__vector_transform(ts__vector_ptr self,
                             ts__vector_transform_cb callback);
int ts__vector_pop(ts__vector_ptr self);

// data query
int ts__vector_get(const ts__vector_ptr self, size_t index, void **item);
ssize_t ts__vector_size(const ts__vector_ptr self);
ssize_t ts__vector_capacity(const ts__vector_ptr self);

#endif  // TISS_VECTOR_H