#include <gtest/gtest.h>

// c++ standard library
#include <iostream>

// TISS include
#include <tiss/vector.h>

TEST(tiss_vector, ts__vector_init) {
  ts__vector_t* vector = NULL;

  ASSERT_EQ(0, ts__vector_init(&vector, sizeof(int64_t)));
  ASSERT_EQ(2, ts__vector_capacity(vector));
  ASSERT_EQ(0, ts__vector_size(vector));

  ts__vector_free(vector);
}

TEST(tiss_vector, ts__vector_push) {
  ts__vector_t* vector = NULL;

  ASSERT_EQ(0, ts__vector_init(&vector, sizeof(int64_t)));
  ASSERT_EQ(2, ts__vector_capacity(vector));
  ASSERT_EQ(0, ts__vector_size(vector));

  for (int64_t item = 0; item < 1000; ++item) {
    ASSERT_EQ(item, ts__vector_push(vector, &item));
    ASSERT_EQ(item + 1, ts__vector_size(vector));
  }
  ASSERT_EQ(1024, ts__vector_capacity(vector));

  ts__vector_free(vector);
}

TEST(tiss_vector, ts__vector_get) {
  ts__vector_t* vector = NULL;

  ASSERT_EQ(0, ts__vector_init(&vector, sizeof(int)));
  ASSERT_EQ(2, ts__vector_capacity(vector));
  ASSERT_EQ(0, ts__vector_size(vector));

  for (int i = 0; i < 1200; ++i) {
    ASSERT_EQ(i, ts__vector_push(vector, &i));
  }

  ASSERT_EQ(2048, ts__vector_capacity(vector));
  ASSERT_EQ(1200, ts__vector_size(vector));

  for (int i = 0; i < 1200; ++i) {
    int item;
    ASSERT_EQ(0, ts__vector_get(vector, i, &item));
    ASSERT_EQ(i, item);
  }

  ts__vector_free(vector);
}