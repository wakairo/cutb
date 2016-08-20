#include "test_helper.h"

CUTB_TEST_GROUP(SeekTest)

CUTB_TEST(SeekToZero)
{
    setup();
    CUTB_ASSERT(TestManager::seekTest(0));
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());
}

CUTB_TEST(SeekAndAdvance)
{
    setup();

    CUTB_ASSERT(TestManager::seekTest(1));
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(2, MockTest::lastID());

    CUTB_ASSERT(TestManager::advanceTest());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());
    CUTB_ASSERT(!TestManager::advanceTest());

    CUTB_ASSERT(TestManager::seekTest(2));
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());

    CUTB_ASSERT(TestManager::seekTest(0));
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());
}

CUTB_TEST(OutOfRange1)
{
    setup();
    CUTB_ASSERT(TestManager::seekTest(0));

    CUTB_ASSERT(!TestManager::seekTest(3));
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());

    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(2, MockTest::lastID());
}

CUTB_TEST(OutOfRange2)
{
    setup();
    CUTB_ASSERT(TestManager::seekTest(0));
    CUTB_ASSERT(!TestManager::seekTest(4));
    CUTB_ASSERT(!TestManager::seekTest(99));
    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT(!TestManager::seekTest(88));
    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());
}

CUTB_TEST_GROUP_END;
