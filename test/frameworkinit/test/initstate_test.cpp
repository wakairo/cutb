#include "cutb_config.h"
#include "cutb/frameworkbase.h"

using cutb::TestManager;

namespace {
class MockTest : public cutb::TestBase {
private:
    static int last_id__;
public:
    static int lastID() {
        return last_id__;
    }
private:
    int id_;
public:
    MockTest(int id) : id_(id) {}
    virtual void testBody() {
        last_id__ = id_;
    }
} mock1(1), mock2(2), mock3(3);
int MockTest::last_id__ = -1;
}


CUTB_TEST_GROUP(InitialStateTest)

CUTB_TEST(GradualTestAddition)
{
    TestManager::runTest();
    CUTB_ASSERT(!TestManager::advanceTest());
    CUTB_ASSERT(!TestManager::seekTest(0));
    CUTB_ASSERT_EQ_LONG(-1, MockTest::lastID());

    TestManager mgr1(mock1, "mock1", __FILE__, __LINE__);
    TestManager mgr2(mock2, "mock2", __FILE__, __LINE__);

    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());

    CUTB_ASSERT(TestManager::advanceTest());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(2, MockTest::lastID());

    CUTB_ASSERT(!TestManager::advanceTest());

    CUTB_ASSERT(TestManager::seekTest(0));
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(1, MockTest::lastID());

    CUTB_ASSERT(TestManager::seekTest(1));
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(2, MockTest::lastID());

    CUTB_ASSERT(!TestManager::seekTest(2));

    TestManager mgr3(mock3, "mock3", __FILE__, __LINE__);

    CUTB_ASSERT(!TestManager::seekTest(99));
    CUTB_ASSERT(!TestManager::seekTest(3));
    CUTB_ASSERT(TestManager::seekTest(2));
    CUTB_ASSERT(TestManager::seekTest(1));
    CUTB_ASSERT(TestManager::seekTest(0));

    CUTB_ASSERT(TestManager::advanceTest());
    CUTB_ASSERT(TestManager::advanceTest());
    TestManager::runTest();
    CUTB_ASSERT_EQ_LONG(3, MockTest::lastID());

    CUTB_ASSERT(!TestManager::advanceTest());
}

CUTB_TEST_GROUP_END;
