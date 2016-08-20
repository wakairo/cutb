#include "cutb_config.h"

CUTB_TEST_GROUP(AssertionTestFailure)

CUTB_TEST(ASSERT_TEST)
{
    void * ptr = NULL;

    CUTB_ASSERT(NULL != ptr);
}

CUTB_TEST(ULONG_TEST)
{
    unsigned long lval = 1;

    CUTB_ASSERT_EQ_ULONG(0 * 1, lval);
}

CUTB_TEST(LONG_TEST)
{
    long lval = -1;

    CUTB_ASSERT_EQ_LONG(2 * 3, lval);
}

CUTB_TEST(DOUBLE_TEST_NG1)
{
    CUTB_ASSERT_EQ_DBL(1 * 1.0, 1.02, 0.01);
}

CUTB_TEST(DOUBLE_TEST_NG2)
{
    CUTB_ASSERT_EQ_DBL(1 * 1000.0, 1002.0, 1.0);
}

CUTB_TEST(DOUBLE_TEST_NG3)
{
    double dval = -1.0;

    CUTB_ASSERT_EQ_DBL(1.0, dval, 0.01);
}

CUTB_TEST_GROUP_END;


CUTB_TEST_GROUP(AssertionTestSuccess)

CUTB_TEST(ASSERT_TEST)
{
    void * ptr = NULL;

    CUTB_ASSERT(NULL == ptr);
}

CUTB_TEST(ULONG_TEST)
{
    unsigned long lval = 1;
    unsigned int ival = 2;
    unsigned short sval = 3;
    unsigned char cval = 4;

    CUTB_ASSERT_EQ_ULONG(0, 0);
    CUTB_ASSERT_EQ_ULONG(1, lval);
    CUTB_ASSERT_EQ_ULONG(2, ival);
    CUTB_ASSERT_EQ_ULONG(3, sval);
    CUTB_ASSERT_EQ_ULONG(4, cval);
}

CUTB_TEST(LONG_TEST)
{
    long lval = -1;
    int ival = -2;
    short sval = -3;
    char cval = -4;

    CUTB_ASSERT_EQ_LONG(0, 0);
    CUTB_ASSERT_EQ_LONG(-1, lval);
    CUTB_ASSERT_EQ_LONG(-2, ival);
    CUTB_ASSERT_EQ_LONG(-3, sval);
    CUTB_ASSERT_EQ_LONG(-4, cval);
}

CUTB_TEST(DOUBLE_TEST)
{
    float fval = -1.0F;
    double dval = 1.0;

    CUTB_ASSERT_EQ_DBL(0.0, 0.0, 0.0);
    CUTB_ASSERT_EQ_DBL(1.0, 1.0, 0.0);
    CUTB_ASSERT_EQ_DBL(1.0, 1.0, 0.01);
    CUTB_ASSERT_EQ_DBL(0.001, 0.002, 0.0011);

    CUTB_ASSERT_EQ_DBL(-1.0, fval, 0.01);
    CUTB_ASSERT_EQ_DBL(1.0, dval, 0.01);
}

CUTB_TEST_GROUP_END;
