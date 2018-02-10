#include "cutb/assert/exit.h"

#include "kexpected.h"
#include "test_helper.h"

namespace {

void parse_with_filepath_test(const char *path, const char *expected)
{
    helper::TestParser tp;
    cutb::Parser::parse(tp, path);
    EXIT_IF_NOT_EQ_CPPOBJ(expected, tp.str());
}

void parse_with_wrong_filepath_test()
{
    helper::TestParser tp;
    bool exception_flag = false;
    try {
        cutb::Parser::parse(tp, "wrong_filepath");
    } catch (const cutb::ArgumentError &) {
        exception_flag = true;
    }
    CUTB_ASSERT(exception_flag);
}
}

int main()
{
    parse_with_filepath_test("cutbtests/g1t1.cpp", KEXPECTED_G1T1);
    parse_with_filepath_test("cutbtests/g2t2.cpp", KEXPECTED_G2T2);
    parse_with_filepath_test("cutbtests/g1t0.cpp", KEXPECTED_G1T0);

    parse_with_wrong_filepath_test();

    return 0;
}
