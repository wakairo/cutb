#ifndef CUTB_FRAMEWORK_SIMPLE_CORE_H
#define CUTB_FRAMEWORK_SIMPLE_CORE_H

#include <cstddef>

/** @file
 * Classes for CUTB simple framework.
 */

namespace cutb {
class TestBase {
public:
    virtual ~TestBase(){};
    virtual void testBody() = 0;
};

/**
 * API class used in CUTB simple framework.
 */
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
    /**
     * Makes the current test move to the test corresponding to the @p idx.
     * If @p idx is out of the test index range, the seeking fails and false is
     * returned.
     *
     * @param idx index of the test to seek to
     * @returns whether the seeking succeeded or not
     */
    static bool seekTest(size_t idx);
    /**
     * Makes the current test move to the next test.
     * When the current test is the last test, the advancement fails and false
     * is returned.
     *
     * @returns whether the advancement succeeded or not.
     */
    static bool advanceTest();
    /**
     * Runs the current test.
     */
    static void runTest();
    /**
     * @returns the test name of the current test.
     */
    static const char *currentTestname();
    /**
     * @returns the file path of the current test.
     */
    static const char *currentFilepath();
    /**
     * @returns the line number of the current test.
     */
    static int currentLineno();
};
}

#endif
