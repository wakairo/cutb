# Asserts

There are four types of assertions of CUTB.

- `CUTB_ASSERT(condition)` - checks `condition`, and if it is true, this assert passes.
- `CUTB_ASSERT_EQ_LONG(expected, actual)` - converts both `expected` and `actual` to `long`, and if they are equal, this assert passes.
- `CUTB_ASSERT_EQ_ULONG(expected, actual)` - converts both `expected` and `actual` to `unsigned long`, and if they are equal, this assert passes.
- `CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)` - calculates the difference between `expected` and `actual`, and if it is within `tolerance`, this assert passes.
