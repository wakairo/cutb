#ifndef CUTB_FRAMEWORK_MINCPP_H
#define CUTB_FRAMEWORK_MINCPP_H

#define CUTB_I_TEST_GROUP_I(test_group_name)                                   \
    namespace CUTB_I_namespace_##test_group_name                               \
    {
#define CUTB_TEST_GROUP(test_group_name) CUTB_I_TEST_GROUP_I(test_group_name)

#define CUTB_TEST_GROUP_END }

#define CUTB_I_TEST_II(testid)                                                 \
    struct testid {                                                            \
        testid();                                                              \
    } testid##_inst;                                                           \
    testid::testid()
#define CUTB_I_TEST_I(test_name) CUTB_I_TEST_II(CUTB_I_testid_##test_name)
#define CUTB_TEST(test_name) CUTB_I_TEST_I(test_name)

#endif
