#ifndef CUTB_FRAMEWORK_SIMPLE_CORE_H
#define CUTB_FRAMEWORK_SIMPLE_CORE_H

#include <cstddef>

namespace cutb {
class TestBase {
public:
    virtual ~TestBase(){};
    virtual void testBody() = 0;
};

class TestManager {
private:
    TestManager *next_;
    TestBase &test_;
    const char *const testname_;
    const char *const filepath_;
    const int lineno_;
    TestBase &testInst() { return test_; }
public:
    TestManager(TestBase &inst, const char *testname, const char *filepath,
                int lineno)
        : next_(NULL), test_(inst), testname_(testname), filepath_(filepath),
          lineno_(lineno)
    {
        addBack(this);
    }

private:
    static TestManager *s_first_;
    static TestManager *s_last_;
    static TestManager *s_current_;
    static void addBack(TestManager *inst);

public:
    static bool seekTest(size_t idx);
    static bool advanceTest();
    static void runTest();
    static const char *currentTestname();
    static const char *currentFilepath();
    static int currentLineno();
};
}

#endif
