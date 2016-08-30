#ifndef CUTB_FRAMEWORKBASE_H
#define CUTB_FRAMEWORKBASE_H

#include <stddef.h>

namespace cutb {
class TestBase {
public:
    virtual ~TestBase() {};
    virtual void testBody() = 0;
};

class TestManager {
private:
    TestManager * next_;
    TestBase &test_;
    TestBase & testInst() {
        return test_;
    }
public:
    TestManager(TestBase &inst)
        : next_(NULL), test_(inst) {
        addBack(this);
    }
private:
    static TestManager * first__;
    static TestManager * last__;
    static TestManager * current__;
    static void addBack(TestManager * inst);
public:
    static bool seekTest(size_t n);
    static bool advanceTest();
    static void runTest();
};
}

#endif
