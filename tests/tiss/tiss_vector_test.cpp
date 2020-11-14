#include <gtest/gtest.h>

// c++ standard library
#include <iostream>

// TISS include
#include <tiss/vector.h>

class tiss_vector_test : public ::testing::Test {
 protected:
  void SetUp() override {
    ASSERT_EQ(0, ts__vector_init(&m_vector, sizeof(int)));
  }

  void TearDown() override { ts__vector_free(m_vector); }

 protected:
  ts__vector_t* m_vector = NULL;
};

TEST_F(tiss_vector_test, ts__vector_init) {
  ASSERT_EQ(2, ts__vector_capacity(m_vector));
  ASSERT_EQ(0, ts__vector_size(m_vector));
}

TEST_F(tiss_vector_test, ts__vector_push_death) {
  int item;
#ifdef NDEBUG
  ASSERT_EQ(EINVAL, ts__vector_push(NULL, &item));
  ASSERT_EQ(EINVAL, ts__vector_push(m_vector, NULL));
#else
  ASSERT_DEATH(ts__vector_push(NULL, &item), "");
  ASSERT_DEATH(ts__vector_push(m_vector, NULL), "");
#endif
}

TEST_F(tiss_vector_test, ts__vector_push) {
  int item;

  for (item = 0; item < 1000; ++item) {
    ASSERT_EQ(item, ts__vector_push(m_vector, &item));
    ASSERT_EQ(item + 1, ts__vector_size(m_vector));
  }
  ASSERT_EQ(1024, ts__vector_capacity(m_vector));
}

TEST_F(tiss_vector_test, ts__vector_get_death) {
  int item;
#ifdef NDEBUG
  ASSERT_EQ(EINVAL, ts__vector_get(NULL, 0, &item));
  ASSERT_EQ(EINVAL, ts__vector_get(m_vector, 0, NULL));
#else
  ASSERT_DEATH(ts__vector_get(NULL, 0, &item), "");
  ASSERT_DEATH(ts__vector_get(m_vector, 0, NULL), "");
#endif
}

TEST_F(tiss_vector_test, ts__vector_get) {
  int item;
  ASSERT_EQ(ENODATA, ts__vector_get(m_vector, 0, &item));

  for (int i = 0; i < 1200; ++i) {
    ASSERT_EQ(i, ts__vector_push(m_vector, &i));
  }

  ASSERT_EQ(2048, ts__vector_capacity(m_vector));
  ASSERT_EQ(1200, ts__vector_size(m_vector));

  for (int i = 0; i < 1200; ++i) {
    ASSERT_EQ(0, ts__vector_get(m_vector, i, &item));
    ASSERT_EQ(i, item);
  }
}
