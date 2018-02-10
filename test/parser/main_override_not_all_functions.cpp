#include <sstream>
#include <string>

#include "cutb/assert/exit.h"

#include "test_helper.h"

namespace {

class TestCounter : public cutb::Parser {
private:
    size_t ntests_;

public:
    size_t ntests() { return ntests_; }
    TestCounter() : ntests_(0) {}
    virtual void at(const TestDef *testdef, const TestGrp *grp,
                    const TestFile *file)
    {
        ++ntests_;
    }
};

class FileEnumerator : public cutb::Parser {
private:
    std::stringstream ss_;

public:
    std::string str() { return ss_.str(); }
    virtual void start(const TestFile *file) { ss_ << file->filepath() << ";"; }
};
}

int main()
{
    TestCounter tc;
    cutb::Parser::parse(tc);
    CUTB_ASSERT_EQ_ULONG(3, tc.ntests());

    FileEnumerator fe;
    cutb::Parser::parse(fe);
    EXIT_IF_NOT_EQ_CPPOBJ("cutbtests/g1t1.cpp;cutbtests/g2t2.cpp;", fe.str());

    return 0;
}
