#ifndef CUTB_BRIDGE_MSVC_H
#define CUTB_BRIDGE_MSVC_H

#include "CppUnitTest.h"

#define CUTB_TEST_GROUP(test_group_name)                                       \
    TEST_CLASS(test_group_name)                                                \
    {

#define CUTB_TEST(test_name) TEST_METHOD(test_name)

#define CUTB_TEST_GROUP_END }

#define CUTB_I_MSVC_IsTrue(x)                                                  \
    Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(x)
#define CUTB_I_MSVC_AreEqual_BIN(x, y)                                         \
    Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(x, y)
#define CUTB_I_MSVC_AreEqual_TER(x, y, z)                                      \
    Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(x, y, z)

#define CUTB_ASSERT(condition) CUTB_I_MSVC_IsTrue(condition)
#define CUTB_ASSERT_EQ_LONG(expected, actual)                                  \
    CUTB_I_MSVC_AreEqual_BIN(static_cast<long>(expected),                      \
                             static_cast<long>(actual));
#define CUTB_ASSERT_EQ_ULONG(expected, actual)                                 \
    CUTB_I_MSVC_AreEqual_BIN(static_cast<unsigned long>(expected),             \
                             static_cast<unsigned long>(actual))
#define CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)                        \
    CUTB_I_MSVC_AreEqual_TER(static_cast<double>(expected),                    \
                             static_cast<double>(actual),                      \
                             static_cast<double>(tolerance))

#endif
