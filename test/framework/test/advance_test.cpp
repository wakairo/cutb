#include <cstring>

#include "test_helper.h"

using std::strcmp;

CUTB_TEST_GROUP(AdvanceTest)

CUTB_TEST(SequentialAccessTest)
{
    setup();
    CUTB_ASSERT(TestManager::seekTest(0));
    CUTB_ASSERT(0 == strcmp("mock1", TestManager::currentTestname()));
    CUTB_ASSERT(0 == strcmp("file1", TestManager::currentFilepath()));
    CUTB_ASSERT_EQ_ULONG(11, TestManager::currentLineno());

    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());
    CUTB_ASSERT(0 == strcmp("mock1", TestManager::currentTestname()));
    CUTB_ASSERT(0 == strcmp("file1", TestManager::currentFilepath()));
    CUTB_ASSERT_EQ_ULONG(11, TestManager::currentLineno());

    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());
    CUTB_ASSERT(0 == strcmp("mock2", TestManager::currentTestname()));
    CUTB_ASSERT(0 == strcmp("file2", TestManager::currentFilepath()));
    CUTB_ASSERT_EQ_ULONG(12, TestManager::currentLineno());

    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(2, MockTest::lastID());

    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(2, MockTest::lastID());
    CUTB_ASSERT(0 == strcmp("mock3", TestManager::currentTestname()));
    CUTB_ASSERT(0 == strcmp("file3", TestManager::currentFilepath()));
    CUTB_ASSERT_EQ_ULONG(13, TestManager::currentLineno());

    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());

    CUTB_ASSERT(!TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());
    CUTB_ASSERT(0 == strcmp("", TestManager::currentTestname()));
    CUTB_ASSERT(0 == strcmp("", TestManager::currentFilepath()));
    CUTB_ASSERT_EQ_ULONG(0, TestManager::currentLineno());

    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());

    MockTest::setLastID(0);

    CUTB_ASSERT(!TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    CUTB_ASSERT(0 == strcmp("", TestManager::currentTestname()));
    CUTB_ASSERT(0 == strcmp("", TestManager::currentFilepath()));
    CUTB_ASSERT_EQ_ULONG(0, TestManager::currentLineno());

    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());

    CUTB_ASSERT(!TestManager::advanceTest());
    CUTB_ASSERT_EQ_LONG(0, MockTest::lastID());
    CUTB_ASSERT(0 == strcmp("", TestManager::currentTestname()));
    CUTB_ASSERT(0 == strcmp("", TestManager::currentFilepath()));
    CUTB_ASSERT_EQ_ULONG(0, TestManager::currentLineno());

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
