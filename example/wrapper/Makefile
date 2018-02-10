cutb_test_path = ../test

CXX = g++
CPPFLAGS = -Wall -MMD -I . -I ../../include
VPATH = ../../src ../../wrapper/src $(cutb_test_path)

target = cutb-wrap
cutb_tests = $(wildcard $(cutb_test_path)/*_test.cpp)
cutb_test_objects = $(patsubst %.cpp, %.o, $(notdir $(cutb_tests)))
objects = cutb_parser_core.o wrapmain.o $(cutb_test_objects)
depends = $(objects:.o=.d)

c_helper_code = cutb_wrapper_chelper.c
wrap_suffix = .wrappedtest

.PHONY: all clean wrap

all: wrap

wrap: $(target) $(c_helper_code)

$(target): $(objects)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

# This is a special rule.
# C helper code file is used to record last-wrapping time.
# Any CUTB tests that has been changed since the time appear in "$?".
# To prevent the target binary from appearing in "$?",
# it is not included in the prerequisites though actually it is a prerequisite.
# Thus, this target should not be called directory, but through wrap target,
# which has the target binary as a prerequisite before this target.
$(c_helper_code): $(cutb_tests)
	./$(target) -s $(wrap_suffix) -c $(c_helper_code) $?

# If any runner does not need the helper file, a dummy file is enough as below.
# dummy: $(cutb_tests)
#	./$(target) -s $(wrap_suffix) $?
#	touch $@

clean:
	rm -f $(target) $(c_helper_code) $(objects) $(depends) *.cpp$(wrap_suffix)

-include $(depends)
