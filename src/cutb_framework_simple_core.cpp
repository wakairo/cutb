#include "cutb/framework/simple/core.h"

using cutb::TestManager;

TestManager *TestManager::s_first_ = NULL;
TestManager *TestManager::s_last_ = NULL;
TestManager *TestManager::s_current_ = NULL;

void TestManager::addBack(TestManager *mgr)
{
    if (NULL == s_first_) {
        s_first_ = mgr;
        s_last_ = mgr;
        s_current_ = mgr;
    } else {
        s_last_->next_ = mgr;
        s_last_ = mgr;
    }
}

bool TestManager::seekTest(size_t idx)
{
    TestManager *mgr = s_first_;
    for (size_t i = 0; i < idx && NULL != mgr; ++i) {
        mgr = mgr->next_;
    }
    if (NULL == mgr) {
        return false;
    }
    s_current_ = mgr;

    return true;
}

bool TestManager::advanceTest()
{
    if (NULL == s_current_) {
        return false;
    }
    s_current_ = s_current_->next_;
    if (NULL == s_current_) {
        return false;
    }

    return true;
}

void TestManager::runTest()
{
    if (NULL == s_current_) {
        return;
    }
    s_current_->testInst().testBody();
}

const char *TestManager::currentTestname()
{
    if (NULL == s_current_) {
        return "";
    }
    return s_current_->testname_;
}

const char *TestManager::currentFilepath()
{
    if (NULL == s_current_) {
        return "";
    }
    return s_current_->filepath_;
}

int TestManager::currentLineno()
{
    if (NULL == s_current_) {
        return 0;
    }
    return s_current_->lineno_;
}
