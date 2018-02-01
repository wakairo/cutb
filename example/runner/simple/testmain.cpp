#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutb/framework/simple/core.h"

using cutb::TestManager;

static int str_to_ulong(const char *str, unsigned long *num)
{
    unsigned long n;
    char *endp;

    errno = 0;
    n = strtoul(str, &endp, 0);
    if (str == endp || ERANGE == errno) {
        return 0;
    }
    *num = n;

    return 1;
}

int main(int argc, char *argv[])
{
    size_t test_start = 0;

    if (2 <= argc) {
        unsigned long n;
        if (0 == str_to_ulong(argv[1], &n)) {
            fprintf(stderr, "error: not a valid number string, '%s'\n",
                    argv[1]);
            exit(EXIT_FAILURE);
        } else {
            const size_t size_t_max = ((size_t)0) - 1;
            if (size_t_max < n) {
                fprintf(stderr, "error: too large,  %lu\n", n);
                exit(EXIT_FAILURE);
            } else {
                test_start = (size_t)n;
            }
        }
    }

    if (!TestManager::seekTest(test_start)) {
        fprintf(stderr, "error: out of the test index range,  %lu\n",
                test_start);
        exit(EXIT_FAILURE);
    } else {
        size_t i = test_start;
        do {
            printf("%s:%d: %s, %lu .. ", TestManager::currentFilepath(),
                   TestManager::currentLineno(), TestManager::currentTestname(),
                   i);
            fflush(stdout);
            TestManager::runTest();
            printf("done\n");
            ++i;
        } while (TestManager::advanceTest());
        printf("%lu tests; no errors detected.\n", i - test_start);
    }

    return 0;
}
