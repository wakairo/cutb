#include "cutb/framework/simple.h"

int main()
{
    do {
        cutb::TestManager::runTest();
    } while (cutb::TestManager::advanceTest());

    return 0;
}
