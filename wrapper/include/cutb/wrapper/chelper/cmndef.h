#ifndef CUTB_WRAPPER_CHELPER_CMNDEF_H
#define CUTB_WRAPPER_CHELPER_CMNDEF_H

#define CUTB_I_CHELPER_TEST_ID_III(former, latter) former##latter
#define CUTB_I_CHELPER_TEST_ID_II(joined, test_name)                           \
    CUTB_I_CHELPER_TEST_ID_III(joined##_, test_name)
#define CUTB_I_CHELPER_TEST_ID_I(test_group_name, test_name)                   \
    CUTB_I_CHELPER_TEST_ID_II(CUTB_I_CHELPER_testid_##test_group_name,         \
                              test_name)
#define CUTB_I_CHELPER_TEST_ID(test_group_name, test_name)                     \
    CUTB_I_CHELPER_TEST_ID_I(test_group_name, test_name)

#endif
