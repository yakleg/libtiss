#include <gtest/gtest.h>

// c++ standard library
#include <iostream>

// TISS include
#include <tiss/vector.h>

TEST(tiss_vector, ts__vector_init) {
  ts__vector_ptr vector = NULL;

  ASSERT_EQ(0, ts__vector_init(&vector, sizeof(int64_t)));
  ASSERT_EQ(2, ts__vector_capacity(vector));
  ASSERT_EQ(0, ts__vector_size(vector));

  ts__vector_free(vector);
}
