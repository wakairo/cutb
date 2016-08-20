#ifndef CUTB_CONFIG_SIMPLE_H
#define CUTB_CONFIG_SIMPLE_H

#include "cutb/frameworkbase.h"

#define CUTB_TEST_GROUP(test_group_name) namespace test_group_name {
#define CUTB_TEST_GROUP_END }

#define CUTB_TEST(test_name) \
    struct test_name : public ::cutb::TestBase{ virtual void testBody(); } test_name##Inst; \
::cutb::TestManager test_name##Manager(test_name##Inst);  \
void test_name::testBody()

#endif