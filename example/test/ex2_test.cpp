#include <stddef.h>

#include "cutb_config.h"

CUTB_TEST_GROUP(Group2)

CUTB_TEST(Test1)
{
    void * ptr = NULL;

    CUTB_ASSERT(NULL == ptr);
}

CUTB_TEST(Test2)
{
    CUTB_ASSERT_EQ_DBL(1.0, 1.02, 0.05);
}

CUTB_TEST(Test3)
{
    double dval = 1.0;

    CUTB_ASSERT_EQ_DBL(1.1, dval, 1.0);
}

CUTB_TEST_GROUP_END;
