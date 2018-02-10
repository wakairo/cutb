#include "test_helper.h"

extern const char *kExpected;

namespace {

typedef cutb::Parser::TestDef TestDef;
typedef cutb::Parser::TestGrp TestGrp;
typedef cutb::Parser::TestGrpEnd TestGrpEnd;

const char *const kTestFile1 = "cutbtests/g1t1.cpp";
const char *const kTestFile2 = "cutbtests/g2t2.cpp";

TestGrp Gb("Gb", kTestFile2, 3);

TestGrp Ga("Ga", kTestFile1, 3);

TestGrpEnd GbEnd(kTestFile2, 5);
TestGrp Gc("Gc", kTestFile2, 7);
TestDef TaGc("Ta", kTestFile2, 9);

TestDef TaGa("Ta", kTestFile1, 5);
TestGrpEnd GaEnd(kTestFile1, 7);

TestDef TbGc("Tb", kTestFile2, 13);
TestGrpEnd GcEnd(kTestFile2, 17);
}

int main()
{
    helper::TestParser tp;
    cutb::Parser::parse(tp);
    EXIT_IF_NOT_EQ_CPPOBJ(kExpected, tp.str());

    return 0;
}
