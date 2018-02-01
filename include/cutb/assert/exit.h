#ifndef CUTB_ASSERT_EXIT_H
#define CUTB_ASSERT_EXIT_H

extern void cutb_assert_fail(int condition, const char *condstr,
                             const char *filename, int lineno);
extern void cutb_assert_eq_long_impl(long expected, long actual,
                                     const char *expectedstr,
                                     const char *actualstr,
                                     const char *filename, int lineno);
extern void cutb_assert_eq_ulong_impl(unsigned long expected,
                                      unsigned long actual,
                                      const char *expectedstr,
                                      const char *actualstr,
                                      const char *filename, int lineno);
extern void cutb_assert_eq_dbl_impl(double expected, double actual,
                                    double tolerance, const char *expectedstr,
                                    const char *actualstr,
                                    const char *tolerancestr,
                                    const char *filename, int lineno);

#define CUTB_ASSERT(condition)                                                 \
    ((condition) ? (void)0 : cutb_assert_fail((condition), #condition,         \
                                              __FILE__, __LINE__))
#define CUTB_ASSERT_EQ_LONG(expected, actual)                                  \
    cutb_assert_eq_long_impl(expected, actual, #expected, #actual, __FILE__,   \
                             __LINE__)
#define CUTB_ASSERT_EQ_ULONG(expected, actual)                                 \
    cutb_assert_eq_ulong_impl(expected, actual, #expected, #actual, __FILE__,  \
                              __LINE__)
#define CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)                        \
    cutb_assert_eq_dbl_impl(expected, actual, tolerance, #expected, #actual,   \
                            #tolerance, __FILE__, __LINE__)

#endif
