#ifndef CUTB_BRIDGE_CPPUTEST_H
#define CUTB_BRIDGE_CPPUTEST_H

#include "CppUTest/TestHarness.h"

#define CUTB_I_WRAPPED_TEST_GROUP(test_group_name)                             \
    TEST_GROUP(test_group_name){};
#define CUTB_I_WRAPPED_TEST(test_group_name, test_name)                        \
    TEST(test_group_name, test_name)

#define CUTB_ASSERT(condition) CHECK(condition)
#define CUTB_ASSERT_EQ_LONG(expected, actual) LONGS_EQUAL(expected, actual)
#define CUTB_ASSERT_EQ_ULONG(expected, actual)                                 \
    UNSIGNED_LONGS_EQUAL(expected, actual)
#define CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)                        \
    DOUBLES_EQUAL(expected, actual, tolerance)

#endif
