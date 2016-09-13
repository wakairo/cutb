CXX = g++
CPPFLAGS = -Wall -MMD -O0 -fprofile-arcs -ftest-coverage -I . -I ../../../src
LDFLAGS = -fprofile-arcs

VPATH = ../../test/ ../../../src/

BIN = all_test
TEST_OBJS = $(patsubst %.cpp, %.o, $(notdir $(wildcard ../../test/*_test.cpp)))
OBJS = frameworkbase.o assert_exit.o testmain.o $(TEST_OBJS)
DEPENDS=$(OBJS:%.o=%.d)

.PHONY: all test clean

all: test

$(BIN): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

test: $(BIN)
	./$<

clean:
	rm -f $(DEPENDS) $(OBJS) $(BIN) $(OBJS:%.o=%.gcda) $(OBJS:%.o=%.gcno) *.gcov

-include $(DEPENDS)
