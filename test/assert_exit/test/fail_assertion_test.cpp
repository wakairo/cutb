#include "cutb_config.h"

CUTB_TEST_GROUP(AssertionFailureTest)

CUTB_TEST(FailAssert)
{
    void *ptr = NULL;

    CUTB_ASSERT(NULL != ptr);
}

CUTB_TEST(FailEqUlong)
{
    unsigned long lval = 1;

    CUTB_ASSERT_EQ_ULONG(0 * 1, lval);
}

CUTB_TEST(FailEqLong)
{
    long lval = -1;

    CUTB_ASSERT_EQ_LONG(2 * 3, lval);
}

CUTB_TEST(FailEqDbl1)
{
    CUTB_ASSERT_EQ_DBL(1 * 1.0, 1.02, 0.01);
}

CUTB_TEST(FailEqDbl2)
{
    CUTB_ASSERT_EQ_DBL(1 * 1000.0, 1002.0, 1.0);
}

CUTB_TEST(FailEqDbl3)
{
    double dval = -1.0;

    CUTB_ASSERT_EQ_DBL(1.0, dval, 0.01);
}

CUTB_TEST_GROUP_END;
