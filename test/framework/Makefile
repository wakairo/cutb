cutb_test_path = test

CXX = g++
CPPFLAGS = -Wall -MMD -O0 -fprofile-arcs -ftest-coverage -I . -I ../../include
LDFLAGS = -fprofile-arcs
VPATH = ../../src $(cutb_test_path)

test_target = testrunner
test_objects = $(patsubst %.cpp, %.o, $(notdir $(wildcard $(cutb_test_path)/*_test.cpp)))
objects = cutb_framework_simple_core.o test_helper.o testmain.o $(test_objects)
depends = $(objects:.o=.d)

.PHONY: all test clean

all: $(test_target)

$(test_target): $(objects)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

test: $(test_target)
	./$<

clean:
	rm -f $(test_target) $(objects) $(depends) $(objects:.o=.gcda) $(objects:.o=.gcno) *.gcov

-include $(depends)
