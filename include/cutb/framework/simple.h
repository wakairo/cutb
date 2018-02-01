#ifndef CUTB_FRAMEWORK_SIMPLE_H
#define CUTB_FRAMEWORK_SIMPLE_H

#include "cutb/framework/simple/core.h"

#define CUTB_I_TEST_GROUP_I(test_group_name)                                   \
    namespace CUTB_I_namespace_##test_group_name                               \
    {
#define CUTB_TEST_GROUP(test_group_name) CUTB_I_TEST_GROUP_I(test_group_name)

#define CUTB_TEST_GROUP_END }

#define CUTB_I_TEST_II(test_name, testid)                                      \
    struct testid : public ::cutb::TestBase {                                  \
        virtual void testBody();                                               \
    } testid##_inst;                                                           \
    ::cutb::TestManager testid##_manager(testid##_inst, #test_name, __FILE__,  \
                                         __LINE__);                            \
    void testid::testBody()
#define CUTB_I_TEST_I(test_name)                                               \
    CUTB_I_TEST_II(test_name, CUTB_I_testid_##test_name)
#define CUTB_TEST(test_name) CUTB_I_TEST_I(test_name)

#endif
