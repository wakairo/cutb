wrapper_code_path = ../../../wrapper
wrapper_bin_path = ../../wrapper
gtest_include_path_option =
gtest_lib_path_option =

CXX = g++
CPPFLAGS = -Wall -MMD -O0 -fprofile-arcs -ftest-coverage -I . -I $(wrapper_code_path)/include $(gtest_include_path_option)
LDFLAGS = -fprofile-arcs -pthread $(gtest_lib_path_option)
LDLIBS = -lgtest -lgtest_main
VPATH = $(wrapper_bin_path)

test_target = testrunner
test_objects = $(patsubst %, %.o, $(notdir $(wildcard $(wrapper_bin_path)/*.wrappedtest)))
objects = $(test_objects)
depends = $(objects:.o=.d)

.PHONY: all clean test build wrap

all: build

wrap:
	$(MAKE) -C $(wrapper_bin_path)

build: wrap
	$(MAKE) $(test_target)

$(test_target): $(objects)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.wrappedtest:

%.wrappedtest.o: %.wrappedtest
	$(COMPILE.cpp) -x c++ $(OUTPUT_OPTION) $<

test: build
	./$(test_target)

clean:
	rm -f $(test_target)  *.o *.d *.gcda *.gcno *.gcov
	$(MAKE) -C $(wrapper_bin_path) clean

-include $(depends)
