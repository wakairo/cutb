#include "cutb_config.h"

CUTB_TEST_GROUP(Group1)

/** Simple assertion */
CUTB_TEST(Test1)
{
    CUTB_ASSERT(true);
}

/** Assertions comparing two variables */
CUTB_TEST(Test2)
{
    CUTB_ASSERT_EQ_LONG(-1, -1);
    CUTB_ASSERT_EQ_ULONG(0, 0);
    CUTB_ASSERT_EQ_DBL(2.0, 2.0, 0.01);
}

CUTB_TEST_GROUP_END;
