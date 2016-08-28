#ifndef CUTB_BRIDGE_MSVC_H
#define CUTB_BRIDGE_MSVC_H

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CUTB_TEST_GROUP(test_group_name) TEST_CLASS(test_group_name) {
#define CUTB_TEST_GROUP_END }

#define CUTB_TEST(test_name) TEST_METHOD(test_name)

#define CUTB_ASSERT(condition) Assert::IsTrue(condition)
#define CUTB_ASSERT_EQ_LONG(expected, actual) \
    Assert::AreEqual(static_cast<long>(expected), static_cast<long>(actual));
#define CUTB_ASSERT_EQ_ULONG(expected, actual) \
    Assert::AreEqual(static_cast<unsigned long>(expected), static_cast<unsigned long>(actual))
#define CUTB_ASSERT_EQ_DBL(expected, actual, tolerance) \
    Assert::AreEqual(static_cast<double>(expected), static_cast<double>(actual), tolerance)

#endif
