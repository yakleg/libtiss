#include <tiss/vector.h>

#if defined __cplusplus
extern "C" {
#endif

struct ts__vector {
  size_t item_size;
  size_t capacity;
  size_t size;
  void *data;
};

#pragma region /* ts__vector_t construction and destruction region */

#ifndef TISS__VECTOR_DEFAULT_CAPACITY
#define TISS__VECTOR_DEFAULT_CAPACITY 2
#endif

int ts__vector_init(ts__vector_t **self, size_t item_size) {
  assert(self != NULL /* self must not be NULL */);
  assert(item_size != 0 /* item_size must not be  0 (zero) */);

  size_t data_size;
  void *data;

  if (self == NULL || item_size == 0) return EINVAL;

  data_size = TISS__VECTOR_DEFAULT_CAPACITY * item_size;
  data = NULL;

  data = malloc(data_size);
  if (data == NULL) {
    return ENOMEM;
  }

  *self = malloc(sizeof(ts__vector_t));
  if (*self == NULL) {
    free(data);
    return ENOMEM;
  }

  **self = (ts__vector_t){.item_size = item_size,
                          .capacity = TISS__VECTOR_DEFAULT_CAPACITY,
                          .size = 0,
                          .data = data};

  return 0;
}

#undef TISS__VECTOR_DEFAULT_CAPACITY

/*  Reserve space enough for the (capacity * item_size)

    parameters:
      - self pointer to ts__vector_t
      - capacity amount of items for reservation of space

    returns:
      - 0 on success
      - EINVAL if self is NULL or capacity is 0 (zero)
      - ENOMEM Out of memory case
*/
int ts__vector_reserve(ts__vector_ptr self, size_t capacity);

/*  Destroy vector */
void ts__vector_free(ts__vector_ptr self) {
  if (self != NULL) {
    if (self->data != NULL) free(self->data);
    free(self);
  }
}

#pragma endregion /* ts__vector_t construction and destruction region */

#pragma region /* ts__vector_t data manipulation region */

/*  Push (copy) item_size of bytes from item to storage

    parameters:
      - self pointer to ts__vector_t
      - item pointer to the data of item_size size

    returns:
      - 0 or positive index of pushed data
      - EINVAL if self is NULL or item is NULL
      - ENOMEM Out of memory case
*/
ssize_t ts__vector_push(ts__vector_ptr self, const void *item);

/*  Traverse through all the items in the vector (self)
    and apply the callback to each.

    parameters:
      - self pointer to ts__vector_t
      - callback pointer to the transformation callback

    returns:
      - 0 or positive amount of transformed data
      - EINVAL if self is NULL or callback is NULL
*/
ssize_t ts__vector_transform(ts__vector_ptr self,
                             ts__vector_transform_cb callback);

/*  Remove one element from the back

    parameters:
      - self pointer to ts__vector_t

    returns:
      - 0 on success
      - ENODATA in case vector is empty
      - EINVAL if self is NULL
*/
int ts__vector_pop(ts__vector_ptr self);

#pragma endregion /* ts__vector_t data manipulation region */

#pragma region /* ts__vector_t data query region */

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
int ts__vector_get(const ts__vector_ptr self, size_t index, void *item);

ssize_t ts__vector_size(const ts__vector_ptr self) {
  assert(self != NULL /* self must not be NULL */);

  if (self == NULL) return EINVAL;
  return self->size;
}

ssize_t ts__vector_capacity(const ts__vector_ptr self) {
  assert(self != NULL /* self must not be NULL */);

  if (self == NULL) return EINVAL;
  return self->capacity;
}

#pragma endregion /* ts__vector_t data query region */

#if defined __cplusplus
}
#endif
