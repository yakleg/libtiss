#include <tiss/vector.h>

#if defined __cplusplus
extern "C" {
#endif

#ifndef TISS__VECTOR_DEFAULT_CAPACITY
#define TISS__VECTOR_DEFAULT_CAPACITY 2
#endif

#define __PTR_OF(self, index) ((self)->data + (index) * (self)->item_size)

static_assert(TISS__VECTOR_DEFAULT_CAPACITY % 2 == 0,
              "TISS__VECTOR_DEFAULT_CAPACITY must be even");

struct ts__vector {
  size_t item_size;
  size_t capacity;
  size_t size;
  void *data;
};

int ts__vector_init(ts__vector_t **self, size_t item_size) {
  /* preconditions */
  assert(self != NULL /* self must not be NULL */);
  assert(item_size != 0 /* item_size must not be  0 (zero) */);
  assert(item_size < SSIZE_MAX /* item_size too big */);

  if (self == NULL || item_size == 0) return EINVAL;
  if (item_size > SSIZE_MAX) return E2BIG;
  /* preconditions */

  size_t data_size;
  void *data;

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

int ts__vector_reserve(ts__vector_t *self, size_t capacity) {
  /* preconditions */
  assert(self != NULL /* self must not be NULL */);
  assert(capacity != 0 /* capacity must not be  0 (zero) */);
  assert(capacity < SSIZE_MAX /* capacity too big */);

  if (self == NULL || capacity == 0 || capacity < self->size) return EINVAL;
  if (capacity > SSIZE_MAX) return E2BIG;
  if (self->capacity >= capacity) return 0; /* nothing to do */
  /* preconditions */

  size_t new_capacity;
  void *new_data;

  new_capacity = self->capacity;
  while (new_capacity < capacity) new_capacity *= 2;

  new_data = realloc(self->data, new_capacity * self->item_size);
  if (new_data == NULL) return ENOMEM;

  self->data = new_data;
  self->capacity = new_capacity;

  return 0;
}

/* Shrink size of data array if (size <= capacity / 2)

    parameters:
      - self pointer to ts__vector_t

    returns:
      - 0 on success
      - EINVAL if self is NULL
      - ENOMEM Out of memory case
*/
int ts__vector_shrink(ts__vector_t *self) {
  /* preconditions */
  assert(self != NULL /* self must not be NULL */);

  if (self == NULL) return EINVAL;
  /* preconditions */
  size_t capacity = self->capacity;
  void *data = self->data;

  while (self->size <= capacity / 2) {
    capacity /= 2;
    data = realloc(data, capacity * self->item_size);
    if (data == NULL) return ENOMEM;

    self->data = data;
    self->capacity = capacity;
  }

  return 0;
}

void ts__vector_free(ts__vector_t *self) {
  if (self != NULL) {
    if (self->data != NULL) free(self->data);
    free(self);
  }
}

ssize_t ts__vector_push(ts__vector_t *self, const void *item) {
  /* preconditions */
  assert(self != NULL /* self must not be NULL */);
  assert(item != NULL /* item must not be NULL */);

  if (self == NULL || item == NULL) return EINVAL;
  /* preconditions */

  ssize_t index = 0;
  void *dest;
  int error;

  error = ts__vector_reserve(self, self->size + 1);
  if (error != 0) return error;

  index = self->size;
  dest = __PTR_OF(self, index);
  memcpy(dest, item, self->item_size);

  self->size++;

  return index;
}

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
                             ts__vector_transform_cb callback) {
  /* preconditions */
  assert(self != NULL /* self must not be NULL */);
  assert(callback != NULL /* callback must not be NULL */);

  if (self == NULL || callback == NULL) return EINVAL;
  /* preconditions */

  ssize_t index;
  void *item;

  for (index = 0; index < self->size; ++index) {
    item = __PTR_OF(self, index);
    callback(self, index, item);
  }

  return index + 1;
}

/*  Remove one element from the back

    parameters:
      - self pointer to ts__vector_t

    returns:
      - 0 on success
      - ENODATA in case vector is empty
      - EINVAL if self is NULL
*/
int ts__vector_pop(ts__vector_t *self) {
  /* preconditions */
  assert(self != NULL /* self must not be NULL */);

  if (self == NULL) return EINVAL;
  if (self->size == 0) return ENODATA;
  /* preconditions */

  void *data;
  self->size--;
  // Todo: shrik it?
  return 0;
}

int ts__vector_get(const ts__vector_t *self, size_t index, void *item) {
  /* preconditions */
  assert(self != NULL /* self must not be NULL */);
  assert(item != NULL /* item ptr must not be NULL */);

  if (self == NULL || item == NULL) return EINVAL;
  if (index >= self->size) return ENODATA;
  /* preconditions */

  const void *src = __PTR_OF(self, index);
  memcpy(item, src, self->item_size);

  return 0;
}

ssize_t ts__vector_size(const ts__vector_t *self) {
  /* preconditions */
  assert(self != NULL /* self must not be NULL */);

  if (self == NULL) return EINVAL;
  /* preconditions */

  return self->size;
}

ssize_t ts__vector_capacity(const ts__vector_t *self) {
  assert(self != NULL /* self must not be NULL */);

  if (self == NULL) return EINVAL;
  return self->capacity;
}

#pragma endregion /* ts__vector_t data query region */

#undef __PTR_OF
#undef TISS__VECTOR_DEFAULT_CAPACITY

#if defined __cplusplus
}
#endif
