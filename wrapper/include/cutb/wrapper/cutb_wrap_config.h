#ifndef CUTB_WRAPPER_CUTB_WRAP_CONFIG_H
#define CUTB_WRAPPER_CUTB_WRAP_CONFIG_H

#define CUTB_I_WRAPPER_TEST_POSITION_STRING_III(former, latter) former##latter
#define CUTB_I_WRAPPER_TEST_POSITION_STRING_II(joined, lineno)                 \
    CUTB_I_WRAPPER_TEST_POSITION_STRING_III(joined##_, lineno)
#define CUTB_I_WRAPPER_TEST_POSITION_STRING_I(test_name, lineno)               \
    CUTB_I_WRAPPER_TEST_POSITION_STRING_II(                                    \
        CUTB_I_WRAPPER_testposstr_##test_name, lineno)
#define CUTB_I_WRAPPER_TEST_POSITION_STRING(test_name, lineno)                 \
    CUTB_I_WRAPPER_TEST_POSITION_STRING_I(test_name, lineno)

#ifdef __cplusplus

#define CUTB_I_NAMESPACE_STRING(test_group_name)                               \
    CUTB_I_namespace_##test_group_name
#define CUTB_I_WRAPPER_TEST_ID(test_group_name, test_name, lineno)             \
    CUTB_I_NAMESPACE_STRING(test_group_name)                                   \
    ::CUTB_I_WRAPPER_TEST_POSITION_STRING(test_name, lineno)
#define CUTB_TEST_GROUP(test_group_name)                                       \
    namespace CUTB_I_NAMESPACE_STRING(test_group_name)                         \
    {
#define CUTB_TEST_GROUP_END }

#else

#define CUTB_I_WRAPPER_TEST_ID(test_group_name, test_name, lineno)             \
    CUTB_I_WRAPPER_TEST_POSITION_STRING(test_name, lineno)
#define CUTB_TEST_GROUP(test_group_name)
#define CUTB_TEST_GROUP_END

#endif

#define CUTB_TEST(test_name)                                                   \
    static void CUTB_I_WRAPPER_TEST_POSITION_STRING(test_name, __LINE__)()

#endif
