cutb_test_path = cutbtests

CXX = g++
CPPFLAGS = -Wall -MMD -O0 -fprofile-arcs -ftest-coverage -I . -I ../../include
LDFLAGS = -fprofile-arcs
VPATH = ../../src $(cutb_test_path)

link_command = $(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

test_binaries = \
parse_f0g0_test.bin \
parse_g1t0_test.bin \
parse_g1t1_test.bin \
parse_f2g3_test.bin \
onefile.bin \
override_not_all_functions.bin \
crossing_static_initialization_order.bin

tests = $(test_binaries:.bin=.test)

err_test_binaries = \
err_orphanedtestdef.bin \
err_extraneous_group_ending.bin \
err_beginning_before_ending.bin

err_tests = $(err_test_binaries:.bin=.test)

main_objects = $(patsubst %.cpp, %.o, $(wildcard main_*.cpp))
test_objects = $(patsubst %.cpp, %.o, $(notdir $(wildcard cutbtests/*.cpp)))
kexpected_objects = $(patsubst %.cpp, %.o, $(wildcard kexpected_*.cpp))
objects = cutb_parser_core.o cutb_assert_exit.o $(main_objects) $(test_objects) $(kexpected_objects)
depends = $(objects:.o=.d)

.PHONY: all test clean $(tests) $(err_tests)

all: $(test_binaries) $(err_test_binaries)

test: all $(tests) $(err_tests)

$(tests): %.test: %.bin
	./$<

$(err_tests): %.test: %.bin
	! ./$< 2> $@.errmsg.actual
	diff $@.errmsg.expected $@.errmsg.actual

$(err_test_binaries): %.bin: %.o cutb_parser_core.o main_minimum.o
	$(link_command)

parse_f0g0_test.bin: cutb_parser_core.o main_parse.o kexpected_f0g0.o
	$(link_command)

parse_g1t0_test.bin: cutb_parser_core.o main_parse.o kexpected_g1t0.o g1t0.o
	$(link_command)

parse_g1t1_test.bin: cutb_parser_core.o main_parse.o kexpected_g1t1.o g1t1.o
	$(link_command)

parse_f2g3_test.bin: cutb_parser_core.o main_parse.o kexpected_f2g3.o g1t1.o g2t2.o
	$(link_command)

onefile.bin: cutb_parser_core.o cutb_assert_exit.o main_onefile.o g1t0.o g1t1.o g2t2.o
	$(link_command)

override_not_all_functions.bin: cutb_parser_core.o cutb_assert_exit.o main_override_not_all_functions.o g1t1.o g2t2.o
	$(link_command)

crossing_static_initialization_order.bin: cutb_parser_core.o main_crossing_static_initialization_order.o kexpected_f2g3.o
	$(link_command)


clean:
	rm -f $(test_binaries) $(err_test_binaries) $(objects) $(depends) $(objects:.o=.gcda) $(objects:.o=.gcno) *.gcov $(err_tests:%=%.errmsg.actual)

-include $(depends)
