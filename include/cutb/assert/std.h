#ifndef CUTB_ASSERT_STD_H
#define CUTB_ASSERT_STD_H

#include <assert.h>

#ifdef __cplusplus
#include <cmath>
#define CUTB_I_FABS(x) std::fabs(x)
#else
#include <math.h>
#define CUTB_I_FABS(x) fabs(x)
#endif

#define CUTB_ASSERT(condition) assert(condition)
#define CUTB_ASSERT_EQ_LONG(expected, actual)                                  \
    assert((long)expected == (long)actual)
#define CUTB_ASSERT_EQ_ULONG(expected, actual)                                 \
    assert((unsigned long)expected == (unsigned long)actual)
#define CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)                        \
    assert(CUTB_I_FABS((double)expected - actual) <= tolerance)

#endif
