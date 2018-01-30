#ifndef CUTB_ASSERT_STD_H
#define CUTB_ASSERT_STD_H

#include <assert.h>
#include <math.h>

#define CUTB_ASSERT(condition) assert(condition)
#define CUTB_ASSERT_EQ_LONG(expected, actual) assert(expected == actual)
#define CUTB_ASSERT_EQ_ULONG(expected, actual) assert(expected == actual)
#define CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)                        \
    assert(fabs(expected - actual) <= tolerance)

#endif
