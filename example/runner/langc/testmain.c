#include "cutb/wrapper/chelper.h"

int main()
{
    size_t i;
    size_t n;

    n = cutb_ntests();
    for (i = 0; i < n; ++i) {
        cutb_run_test(i);
    }

    return 0;
}
