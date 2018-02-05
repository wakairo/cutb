#include "cutb_config.h"

/** The basic usage of CUTB assertions */
CUTB_TEST_GROUP(BasicAssertionUsageTest)

/** Condition check by using the simple assertion */
CUTB_TEST(ConditionCheck)
{
    int ivar = 1;

    CUTB_ASSERT(0 < ivar);
}

/** Assertions comparing two values */
CUTB_TEST(TwoValuesComparison)
{
    int ivar = -1;
    unsigned int uivar = 0;
    double dvar = 2.0;

    CUTB_ASSERT_EQ_LONG(-1, ivar);
    CUTB_ASSERT_EQ_ULONG(0, uivar);
    CUTB_ASSERT_EQ_DBL(2.0, dvar, 0.01);
}

CUTB_TEST_GROUP_END;
