#ifndef CUTB_PARSER_CUTB_PARSE_CONFIG_H
#define CUTB_PARSER_CUTB_PARSE_CONFIG_H

#include "cutb/assert/std.h" /* Any header works if it handles CUTB asserts well. */

#include "cutb/parser/core.h"

#define CUTB_I_TEST_GROUP_II(test_group_name, lineno)                          \
    namespace CUTB_I_namespace_##test_group_name                               \
    {                                                                          \
        static ::cutb::Parser::TestGrp CUTB_I_PARSER_testgroup_inst_##lineno(  \
            #test_group_name, __FILE__, __LINE__);
#define CUTB_I_TEST_GROUP_I(test_group_name, lineno)                           \
    CUTB_I_TEST_GROUP_II(test_group_name, lineno)
#define CUTB_TEST_GROUP(test_group_name)                                       \
    CUTB_I_TEST_GROUP_I(test_group_name, __LINE__)

#define CUTB_I_TEST_GROUP_END_II(lineno)                                       \
    static ::cutb::Parser::TestGrpEnd                                          \
        CUTB_I_PARSER_testgroupend_inst_##lineno(__FILE__, __LINE__);          \
    }
#define CUTB_I_TEST_GROUP_END_I(lineno) CUTB_I_TEST_GROUP_END_II(lineno)
#define CUTB_TEST_GROUP_END CUTB_I_TEST_GROUP_END_I(__LINE__)

#define CUTB_I_TEST_II(test_name, lineno)                                      \
    static ::cutb::Parser::TestDef CUTB_I_PARSER_test_inst_##lineno(           \
        #test_name, __FILE__, __LINE__);                                       \
    inline void CUTB_I_PARSER_fakefunc_##lineno()
#define CUTB_I_TEST_I(test_name, lineno) CUTB_I_TEST_II(test_name, lineno)
#define CUTB_TEST(test_name) CUTB_I_TEST_I(test_name, __LINE__)

#endif
