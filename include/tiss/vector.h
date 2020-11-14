#ifndef TISS_VECTOR_H
#define TISS_VECTOR_H

#include <tiss/sys.h>

#if defined __cplusplus
extern "C" {
#endif

typedef struct ts__vector ts__vector_t;

struct ts_vector;

typedef int (*ts__vector_transform_cb)(ts__vector_t *self, size_t index,
                                       void *item);

/*  Initialize an instance of ts__vector_t
    through the double-pointer using malloc

    parameters:
      - self double-pointer to be initialazed
      - item_size exact size of the item

    returns:
      - 0 on success
      - EINVAL if self double-pointer is NULL or item_size is 0 (zero)
      - E2BIG in case item size > SSIZE_MAX
      - ENOMEM Out of memory case
*/
int ts__vector_init(ts__vector_t **self, size_t item_size);

/*  Reserve space enough for the (capacity * item_size)

    parameters:
      - self pointer to ts__vector_t
      - capacity amount of items for reservation of space

    returns:
      - 0 on success
      - EINVAL if self is NULL or capacity is 0 (zero)
        or capacity < amount of items invector
      - E2BIG in case capacity > SSIZE_MAX
      - ENOMEM Out of memory case
*/
int ts__vector_reserve(ts__vector_t *self, size_t capacity);

/* Shrink size of data array if (size <= capacity / 2)

    parameters:
      - self pointer to ts__vector_t

    returns:
      - 0 on success
      - EINVAL if self is NULL
      - ENOMEM Out of memory case
*/
int ts__vector_shrink(ts__vector_t *self);

/*  Destroy vector */
void ts__vector_free(ts__vector_t *self);

/*  Push (copy) item_size of bytes from item to storage

    parameters:
      - self pointer to ts__vector_t
      - item pointer to the data of item_size size

    returns:
      - 0 or positive index of pushed data
      - EINVAL if self is NULL or item is NULL
      - ENOMEM Out of memory case
*/
ssize_t ts__vector_push(ts__vector_t *self, const void *item);

/*  Traverse through all the items in the vector (self)
    and apply the callback to each.

    parameters:
      - self pointer to ts__vector_t
      - callback pointer to the transformation callback

    returns:
      - 0 or positive amount of transformed data
      - EINVAL if self is NULL or callback is NULL
*/
ssize_t ts__vector_transform(ts__vector_t *self,
                             ts__vector_transform_cb callback);

/*  Remove one element from the back

    parameters:
      - self pointer to ts__vector_t

    returns:
      - 0 on success
      - ENODATA in case vector is empty
      - EINVAL if self is NULL
*/
int ts__vector_pop(ts__vector_t *self);

/*  Retrieve copy of the item by index

    parameters:
      - self pointer to ts__vector_t
      - index of the item
      - item double-pointer where to copy

    returns:
      - 0 on success
      - ENODATA in case there is no such item
      - EINVAL if self is NULL or item is NULL
*/
int ts__vector_get(const ts__vector_t *self, size_t index, void *item);

/*  Retrieve amount of items stored in the vector

    parameters:
      - self pointer to ts__vector_t

    returns:
      - 0 or positive size of the vector
      - EINVAL if self is NULL
*/
ssize_t ts__vector_size(const ts__vector_t *self);

/*  Retrieve amount of reserved space in items

    parameters:
      - self pointer to ts__vector_t

    returns:
      - 0 or positive capacity of the vector
      - EINVAL if self is NULL
*/
ssize_t ts__vector_capacity(const ts__vector_t *self);

#if defined __cplusplus
}
#endif

#endif  // TISS_VECTOR_H