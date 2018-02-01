#include <cstring>

#include "cutb/framework/simple.h"

using cutb::TestManager;

int main(int argc, char *argv[])
{
    if (2 <= argc) {
        do {
            if (0 == std::strcmp(argv[1], TestManager::currentTestname())) {
                TestManager::runTest();
            }
        } while (TestManager::advanceTest());
    }

    return 0;
}
