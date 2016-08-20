#include "cutb/frameworkbase.h"

using cutb::TestManager;

TestManager * TestManager::first__ = NULL;
TestManager * TestManager::last__ = NULL;
TestManager * TestManager::current__ = NULL;

void TestManager::addBack(TestManager * mgr)
 {
            if (NULL == first__) {
                first__ = mgr;
                last__ = mgr;
                current__ = mgr;
            }
            else {
                last__->next_ = mgr;
                last__ = mgr;
            }
}

bool TestManager::seekTest(size_t n) {
            TestManager * mgr = first__;
            for (size_t i = 0; i < n && NULL != mgr; ++i) {
                mgr = mgr->next_;
            }
            if (NULL == mgr) {
                return false;
            }
            current__ = mgr;

            return true;
}

bool TestManager::advanceTest() {
    if (NULL == current__) {
        return false;
    }
    current__ = current__->next_;
    if (NULL == current__) {
        return false;
    }

    return true;
}

void TestManager::runTest() {
    if (NULL == current__) {
        return;
    }
    current__->testInst().testBody();
}
