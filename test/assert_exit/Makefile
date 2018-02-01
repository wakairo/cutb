cutb_test_path = test

CXX = g++
CPPFLAGS = -Wall -MMD -O0 -fprofile-arcs -ftest-coverage -I . -I ../../include
LDFLAGS = -fprofile-arcs
VPATH = ../../src $(cutb_test_path)

success_target = success_testrunner
fail_target = fail_testrunner
success_objects = success_testmain.o success_assertion_test.o
fail_objects = fail_testmain.o fail_assertion_test.o
common_objects = cutb_framework_simple_core.o cutb_assert_exit.o
objects = $(common_objects) $(success_objects) $(fail_objects)
depends = $(objects:.o=.d)

fail_tests = \
FailAssert.test \
FailEqUlong.test \
FailEqLong.test \
FailEqDbl1.test \
FailEqDbl2.test \
FailEqDbl3.test

.PHONY: all test clean success.test $(fail_tests)

all: $(success_target) $(fail_target)

$(success_target): $(common_objects) $(success_objects)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

success.test: $(success_target)
	./$<

$(fail_target): $(common_objects) $(fail_objects)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(fail_tests): %.test: $(fail_target)
	! ./$< $* 2> $@.errmsg.actual
	diff $@.errmsg.expected $@.errmsg.actual

test: all success.test $(fail_tests)

clean:
	rm -f $(success_target) $(fail_target) $(objects) $(depends) $(objects:.o=.gcda) $(objects:.o=.gcno) *.gcov $(fail_tests:%=%.errmsg.actual)

-include $(depends)
