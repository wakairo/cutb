#ifndef CUTB_BRIDGE_GTEST_H
#define CUTB_BRIDGE_GTEST_H

#include "gtest/gtest.h"

#define CUTB_I_WRAPPED_TEST_GROUP(test_group_name)
#define CUTB_I_WRAPPED_TEST(test_group_name, test_name)                        \
    TEST(test_group_name, test_name)

#define CUTB_ASSERT(condition) ASSERT_TRUE(condition)
#define CUTB_ASSERT_EQ_LONG(expected, actual)                                  \
    ASSERT_EQ(static_cast<long>(expected), static_cast<long>(actual));
#define CUTB_ASSERT_EQ_ULONG(expected, actual)                                 \
    ASSERT_EQ(static_cast<unsigned long>(expected),                            \
              static_cast<unsigned long>(actual))
#define CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)                        \
    ASSERT_NEAR(static_cast<double>(expected), static_cast<double>(actual),    \
                static_cast<double>(tolerance))

#endif
