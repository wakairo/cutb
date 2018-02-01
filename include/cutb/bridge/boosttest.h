#ifndef CUTB_BRIDGE_BOOSTTEST_H
#define CUTB_BRIDGE_BOOSTTEST_H

#include <cmath>

#include <boost/test/unit_test.hpp>

#define CUTB_TEST_GROUP(test_group_name) BOOST_AUTO_TEST_SUITE(test_group_name)
#define CUTB_TEST_GROUP_END BOOST_AUTO_TEST_SUITE_END()
#define CUTB_TEST(test_name) BOOST_AUTO_TEST_CASE(test_name)

#define CUTB_ASSERT(condition) BOOST_REQUIRE(condition);
#define CUTB_ASSERT_EQ_LONG(expected, actual)                                  \
    BOOST_REQUIRE_EQUAL(static_cast<long>(expected), static_cast<long>(actual));
#define CUTB_ASSERT_EQ_ULONG(expected, actual)                                 \
    BOOST_REQUIRE_EQUAL(static_cast<unsigned long>(expected),                  \
                        static_cast<unsigned long>(actual));
#define CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)                        \
    BOOST_REQUIRE(std::fabs(static_cast<double>(expected) - actual) <=         \
                  tolerance);

#endif
