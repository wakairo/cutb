#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <cstdlib>
#include <iostream>

#define EXIT_IF_NOT_EQ_CPPOBJ(expected, actual)                                \
    exit_if_not_eq_cppobj(expected, actual, #expected, #actual, __FILE__,      \
                          __LINE__)

template <class Expected, class Actual>
inline void
exit_if_not_eq_cppobj(Expected expected, Actual actual, const char *expectedstr,
                      const char *actualstr, const char *filename, int lineno)
{
    if (expected != actual) {
        std::cerr << std::endl
                  << filename << ':' << lineno << ": EXIT_IF_NOT_EQ_CPPOBJ("
                  << expectedstr << ", " << actualstr << ") failed. ["
                  << expected << " != " << actual << ']' << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

#include <sstream>
#include <string>

#include "cutb/parser/core.h"

namespace helper {

class TestParser : public cutb::Parser {
private:
    std::stringstream ss_;

public:
    std::string str() { return ss_.str(); }

    virtual void start(const TestFile *file)
    {
        ss_ << "FS:" << file->filepath() << ";";
    }
    virtual void end(const TestFile *file)
    {
        ss_ << "FE:" << file->filepath() << ";";
    };
    virtual void start(const TestGrp *grp, const TestFile *file)
    {
        ss_ << "GS:";
        ss_ << grp->grpname() << grp->lineno();
        ss_ << file->filepath();
        ss_ << ";";
    };
    virtual void end(const TestGrp *grp, const TestFile *file)
    {
        ss_ << "GE:";
        ss_ << grp->grpname() << grp->lineno();
        ss_ << file->filepath();
        ss_ << ";";
    };
    virtual void at(const TestDef *testdef, const TestGrp *grp,
                    const TestFile *file)
    {
        ss_ << testdef->testname() << testdef->lineno();
        ss_ << grp->grpname();
        ss_ << file->filepath();
        ss_ << ";";
    }
};
}

#endif
