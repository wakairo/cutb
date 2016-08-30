#ifndef CUTB_CONFIG_ASSERT_EXIT_H
#define CUTB_CONFIG_ASSERT_EXIT_H

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void cutb_assert_fail(int condition, const char * condstr,
                      const char *filename, int lineno)
{
    fprintf(stderr, "\n%s:%d: CUTB_ASSERT(%s) failed.\n",
            filename, lineno, condstr);
    exit(EXIT_FAILURE);
}

void cutb_assert_eq_long_impl(long expected, long actual, const char * expectedstr, const char * actualstr, const char *filename, int lineno)
{
    if (expected !=  actual) {
        fprintf(stderr, "\n%s:%d: CUTB_ASSERT_EQ_LONG(%s, %s) failed. [%ld != %ld]\n",
                filename, lineno, expectedstr, actualstr, expected, actual);
        exit(EXIT_FAILURE);
    }
}

void cutb_assert_eq_ulong_impl(unsigned long expected, unsigned long actual, const char * expectedstr, const char * actualstr, const char *filename, int lineno)
{
    if (expected !=  actual) {
        fprintf(stderr, "\n%s:%d: CUTB_ASSERT_EQ_ULONG(%s, %s) failed. [%lu != %lu]\n",
                filename, lineno, expectedstr, actualstr, expected, actual);
        exit(EXIT_FAILURE);
    }
}

void cutb_assert_eq_dbl_impl(double expected, double actual, double tolerance,
                             const char * expectedstr, const char * actualstr, const char * tolerancestr,
                             const char *filename, int lineno)
{
    if (fabs(expected - actual) > tolerance) {
        fprintf(stderr, "\n%s:%d: CUTB_ASSERT_EQ_DBL(%s, %s, %s) failed. [fabs(%f - %f) > %f]\n",
                filename, lineno,
                expectedstr, actualstr, tolerancestr,
                expected, actual, tolerance);
        exit(EXIT_FAILURE);
    }
}

#endif
