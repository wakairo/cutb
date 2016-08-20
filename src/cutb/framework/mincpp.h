#ifndef CUTB_CONFIG_MINCPP_H
#define CUTB_CONFIG_MINCPP_H

#define CUTB_TEST_GROUP(test_group_name) namespace test_group_name {
#define CUTB_TEST_GROUP_END }
#define CUTB_TEST(test_name) struct test_name{ test_name();} test_name##Inst; test_name::test_name()

#endif
