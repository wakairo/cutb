#!/bin/sh

make -C test/assert_exit "$@"
make -C test/framework "$@"
make -C test/frameworkinit "$@"
make -C test/parser "$@"
make -C test/utils "$@"
make -C test/wrapper "$@"
make -C example/runner/boosttest "$@"
make -C example/runner/cpputest "$@"
make -C example/runner/gtest "$@"
make -C example/runner/langc "$@"
make -C example/runner/mincpp "$@"
make -C example/runner/simple "$@"
