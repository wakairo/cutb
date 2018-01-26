#!/bin/sh

make -C test/assert_exit "$@"
make -C test/framework "$@"
make -C test/frameworkinit "$@"
make -C example/runner/boosttest "$@"
make -C example/runner/mincpp "$@"
make -C example/runner/simple "$@"
