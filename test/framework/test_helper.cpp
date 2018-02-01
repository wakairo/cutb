#include "test_helper.h"

namespace test_helper {
int MockTest::s_last_id_ = -1;
}

static size_t test_count = 0;
size_t get_count(void)
{
    return test_count;
}

void setup(void)
{
    static test_helper::MockTest mock1(1), mock2(2), mock3(3);
    static cutb::TestManager mgr1(mock1, "mock1", "file1", 11);
    static cutb::TestManager mgr2(mock2, "mock2", "file2", 12);
    static cutb::TestManager mgr3(mock3, "mock3", "file3", 13);

    ++test_count;
    test_helper::MockTest::setLastID(0);
    return;
}
