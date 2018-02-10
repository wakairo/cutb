wrapper_code_path = ../../wrapper

CXX = g++
CPPFLAGS = -Wall -MMD -O0 -fprofile-arcs -ftest-coverage -I . -I ../../include
LDFLAGS = -fprofile-arcs
VPATH = ../../src $(wrapper_code_path)/src

default_cutb_test = cutb_test_valid.cpp
c_helper_code = c_helper.h
usage_pattern = usage:.*$(test_target)

tests = \
prefix_option.test \
suffix_option.test \
c_helper.test

err_tests = \
err_invalid_option.test \
err_no_argument_for_suffix_option.test \
err_no_argument_for_prefix_option.test \
err_invalid_test_name.test \
err_no_filename_in_a_path.test \
err_on_opening_wrap_file.test \
err_on_opening_c_helper_file.test

test_target = cutb-wrap
test_objects = $(default_cutb_test:.cpp=.o) cutb_test_invalid.o
objects = cutb_parser_core.o wrapmain.o $(test_objects)
depends = $(objects:.o=.d)

.PHONY: all clean test $(tests) $(err_tests)

all: $(test_target)

$(test_target): $(objects)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f $(test_target) $(c_helper_code) $(objects) $(depends) $(objects:.o=.gcda) $(objects:.o=.gcno) *.gcov test_prefix.* *.test_suffix *.errmsg.actual

test: $(tests) $(err_tests)

prefix_option.test: $(test_target)
	./$< -p test_prefix. $(default_cutb_test)
	ls test_prefix.$(default_cutb_test)

suffix_option.test: $(test_target)
	./$< -s .test_suffix $(default_cutb_test)
	ls $(default_cutb_test).test_suffix

c_helper.test: $(test_target)
	./$< -c $(c_helper_code)
	ls $(c_helper_code)

err_invalid_option.test: $(test_target)
	! ./$< -z 2> $@.errmsg.actual
	grep $(usage_pattern) $@.errmsg.actual

err_no_argument_for_suffix_option.test: $(test_target)
	! ./$< -s 2> $@.errmsg.actual
	grep $(usage_pattern) $@.errmsg.actual

err_no_argument_for_prefix_option.test: $(test_target)
	! ./$< -p 2> $@.errmsg.actual
	grep $(usage_pattern) $@.errmsg.actual

err_invalid_test_name.test: $(test_target)
	! ./$< non-existent_path 2> $@.errmsg.actual
	grep 'error: unkonwn test file path' $@.errmsg.actual

err_no_filename_in_a_path.test: $(test_target)
	! ./$< -a -s .test_suffix 2> $@.errmsg.actual
	grep 'error: no file name in the test file path' $@.errmsg.actual

err_on_opening_wrap_file.test: $(test_target)
	./$< -s .readonly.test_suffix $(default_cutb_test)
	chmod 400 $(default_cutb_test).readonly.test_suffix
	! ./$< -s .readonly.test_suffix $(default_cutb_test) 2> $@.errmsg.actual
	chmod 600 $(default_cutb_test).readonly.test_suffix
	grep 'error: unable to open wrap file' $@.errmsg.actual

err_on_opening_c_helper_file.test: $(test_target)
	./$< -c $(c_helper_code).readonly.test_suffix
	chmod 400 $(c_helper_code).readonly.test_suffix
	! ./$< -c $(c_helper_code).readonly.test_suffix 2> $@.errmsg.actual
	chmod 600 $(c_helper_code).readonly.test_suffix
	grep 'error: unable to open C helper file' $@.errmsg.actual

-include $(depends)
