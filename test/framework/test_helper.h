#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "cutb_config.h"

#include "cutb/framework/simple/core.h"

extern void setup(void);
extern size_t get_count(void);

namespace test_helper {
class MockTest : public cutb::TestBase {
private:
    static int s_last_id_;

public:
    static int lastID() { return s_last_id_; }
    static void setLastID(int id) { s_last_id_ = id; }

private:
    int id_;

public:
    MockTest(int id) : id_(id) {}
    virtual void testBody() { s_last_id_ = id_; }
};
}

using cutb::TestManager;
using test_helper::MockTest;

#endif
