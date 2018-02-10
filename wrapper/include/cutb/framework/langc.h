#ifndef CUTB_FRAMEWORK_LANGC_H
#define CUTB_FRAMEWORK_LANGC_H

#include "cutb/wrapper/chelper/cmndef.h"

#define CUTB_I_WRAPPED_TEST_GROUP(test_group_name)
#define CUTB_I_WRAPPED_TEST(test_group_name, test_name)                        \
    void CUTB_I_CHELPER_TEST_ID(test_group_name, test_name)()

#endif
