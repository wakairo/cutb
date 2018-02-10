#ifndef CUTB_WRAPPER_CHELPER_H
#define CUTB_WRAPPER_CHELPER_H

#include <stddef.h>

/** @file
 * API functions used in CUTB language C framework.
 */

/**
 * Runs the test corresponding to the @p idx.
 *
 * @param idx index of the test to run.
 */
extern void cutb_run_test(size_t idx);
/**
 * @returns the number of tests.
 */
extern size_t cutb_ntests(void);

#endif
