#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "cutb_config.h"
#include "cutb/frameworkbase.h"

extern void setup(void);
extern size_t get_count(void);

namespace test_helper {
class MockTest : public cutb::TestBase {
private:
    static int last_id__;
public:
    static int lastID() {
        return last_id__;
    }
    static void setLastID(int id) {
        last_id__ = id;
    }
private:
    int id_;
public:
    MockTest(int id) : id_(id) {}
    virtual void testBody() {
        last_id__ = id_;
    }
};
}

using cutb::TestManager;
using test_helper::MockTest;

#endif
