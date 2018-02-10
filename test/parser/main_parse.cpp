#include "test_helper.h"

extern const char *kExpected;

int main()
{
    helper::TestParser tp;
    cutb::Parser::parse(tp);
    EXIT_IF_NOT_EQ_CPPOBJ(kExpected, tp.str());

    return 0;
}
