#include <stddef.h>

#include "cutb_config.h"

/** How to do null check */
CUTB_TEST_GROUP(NullCheckTest)

/** Checking whether a pointer is NULL or not */
CUTB_TEST(PointerCheck)
{
    int *ptr;
    int ivar;

    ptr = NULL;
    CUTB_ASSERT(NULL == ptr);

    ptr = &ivar;
    CUTB_ASSERT(NULL != ptr);
}

CUTB_TEST_GROUP_END;
