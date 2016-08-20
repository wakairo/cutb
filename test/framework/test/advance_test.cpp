#include "test_helper.h"

CUTB_TEST_GROUP(AdvanceTest)

CUTB_TEST(SequentialAccessTest)
{
    setup();
    CUTB_ASSERT(TestManager::seekTest(0));
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());

    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(2, MockTest::lastID());

    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(2, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());

    CUTB_ASSERT(!TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());

    MockTest::setLastID(0);

    CUTB_ASSERT(!TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());

    CUTB_ASSERT(!TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
}

CUTB_TEST(ConsecutiveAdvanceTest1)
{
    setup();
    CUTB_ASSERT(TestManager::seekTest(0));
    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());
    CUTB_ASSERT(!TestManager::advanceTest());
}

CUTB_TEST(ConsecutiveAdvanceTest2)
{
    setup();
    CUTB_ASSERT(TestManager::seekTest(0));
    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT(!TestManager::advanceTest());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
}

CUTB_TEST_GROUP_END;
