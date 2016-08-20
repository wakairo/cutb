#include "test_helper.h"

namespace test_helper {
    class MockTest mock1(1), mock2(2), mock3(3);
    int MockTest::last_id__ = -1;
    cutb::TestManager mgr1(mock1), mgr2(mock2), mgr3(mock3);
}

static size_t test_count = 0;
size_t get_count(void)
{
    return test_count;
}
void setup(void)
{
    ++test_count;
    test_helper::MockTest::setLastID(0);
    return;
}
