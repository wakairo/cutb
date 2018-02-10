CUTB
====

C/C++ Unit Testing Bridge (CUTB)

[![Build Status](https://travis-ci.org/wakairo/cutb.svg?branch=master)](https://travis-ci.org/wakairo/cutb)

The purpose of CUTB is making it possible to run unit tests written in C or C++ in various environments (e.g. operating systems and testing frameworks).
By using CUTB, testing frameworks of Boost, Visual Studio, and so on can be used to execute the unit tests.
Thus, CUTB makes it easy to test software in multiple environments and make it possible to choose the best tool without restriction of a specific environment.

The followings are example use cases of CUTB.

- In cross development for embedded software, running the same unit tests on both a target machine and a host development machine.
- In order to develop software that supports Linux and Windows, running the same unit tests in different suitable ways according to each development environment.
- Using Gcov, which is a tool of GCC, to measure coverage and using Microsoft Visual Studio for debugging.

CUTB test format is simple and makes all the above possible.



## Assumed use cases

- A case where portability of unit tests is required or is thought to be important.
- A case where there is a reason that requires running unit tests in multiple environments, such as to develop software that supports different operating systems, but it is difficult or impossible to make a testing framework work in all the multiple environments.
- A case where because of the domain, internal structure, or something of the developing software, a unique testing system (such as classes, functions, or macros for the testing) have been constructed, so rich features of a testing framework are not important, and it is important to use different frameworks for different environments so that unit tests run stably without any troubles in each environment.
- A case where developing software needs to run in restricted environment, and unit tests for the software also needs to run in the same environment.
- A case of embedded software development where classes or functions are implemented and checked with unit tests on a personal computer with a productive environment and testing framework, and then they are checked with the same unit tests on a real device.

CUTB does not depend on a specific testing framework. Therefore, CUTB makes it possible to use different testing frameworks according to each development environment or each test execution environment, to migrate from one testing framework to another that has fewer problems, and so on.



## Available environments for running tests

### Unit testing frameworks

- Boost Test Library
- Microsoft Unit Testing Framework

### Unit testing frameworks available by using the wrapper

- Google Test
- Cpputest

### CUTB simplified unit testing framework

CUTB offers a simplified unit testing framework.
Because of its small code size and small use of language features, this framework is suitable for running tests in restricted environment, such as a real device running with embedded software, although the framework's features are very limited.



## CUTB test format

### Simple example of a test file

```
#include "cutb_config.h"

CUTB_TEST_GROUP(ArithmeticOperationTest)

CUTB_TEST(Addition)
{
    CUTB_ASSERT_EQ_LONG(2, 1+1);
}

CUTB_TEST(Multiplication)
{
    CUTB_ASSERT_EQ_LONG(6, 2*3);
}

CUTB_TEST_GROUP_END;
```

### Test macros

- `CUTB_TEST_GROUP(test_group_name)` - indicates the beginning of a test group.
- `CUTB_TEST_GROUP_END` - indicates the end of a test group. A semicolon ( ; ) is required just after this macro.
- `CUTB_TEST(test_name)` - defines a test, which must exist between `CUTB_TEST_GROUP` and `CUTB_TEST_GROUP_END`.

A test file can have multiple test groups.

Names that does not contain underscore ( _ ) are recommended for both test names and test group names.
For the details about this recommendation, see [Google Test FAQ](https://github.com/google/googletest/blob/master/googletest/docs/FAQ.md#why-should-not-test-case-names-and-test-names-contain-underscore).

### Assertions

There are four types of assertions of CUTB.

- `CUTB_ASSERT(condition)` - checks `condition`, and if it is true, this assert passes.
- `CUTB_ASSERT_EQ_LONG(expected, actual)` - converts both `expected` and `actual` to `long`, and if they are equal, this assert passes.
- `CUTB_ASSERT_EQ_ULONG(expected, actual)` - converts both `expected` and `actual` to `unsigned long`, and if they are equal, this assert passes.
- `CUTB_ASSERT_EQ_DBL(expected, actual, tolerance)` - calculates the difference between `expected` and `actual`, and if it is within `tolerance`, this assert passes.

### CUTB configuration header (cutb_config.h)

cutb_config.h is a header file that describes configuration for each test execution environment.
Different files, as cutb_config.h, must be prepared for different execution environments.
In compilation, a file is chosen by the include path setting.

For details about the contents of cutb_config.h, see the following section: "Usage according to applications".

The file name does not need to be cutb_config.h, while the file name must be consistent and `#include` directive must specify the same file name.

Also, cutb_config.h can be included indirectly through another header file.
For example, if all test files include test_helper.h, which has helper functions, `#include "cutb_config.h"` can be written in test_helper.h.



## Getting Started

### Setting up an environment for executing examples

The example of Microsoft Unit Testing Framework requires Visual Studio 2012 or later. The community edition is enough to run the example.

The other examples require an POSIX environment (Unix-like environment).
If your OS is Windows, you can use Cygwin, Windows Subsystem for Linux, or a Linux virtual machine using virtualization software, such as VirtualBox.

The POSIX environment needs to have g++, gcov, make (GNU Make), and doxygen.
An installation package for g++ may include gcov.

In Ubuntu, you can install them via:
```
sudo apt install g++ make doxygen
```

An example that uses an external testing framework, such as Boost Test Library, needs the testing framework to be installed in the POSIX environment.
For example, in Ubuntu, you can install Boost Test Library via `sudo apt install libboost-test-dev`.

### Executing the example of Microsoft Unit Testing Framework
1. In Visual Studio, open `cutbExample.sln` in `example/runner/msvc`.
2. From the menu, select **Test > Run > All Tests** to run tests.

### Executing the examples in the POSIX environment.
1. Change directory to one of the directories in `example/runner/`. For example, `cd example/runner/simple/`.
2. Execute `make test` to run tests.
3. Execute `gcov *.gcda` to output the coverage result to files that have the file extension `.gcov`.

### Generating test documentation with Doxygen
1. Change directory to `example/docs/`.
2. Execute `doxygen Doxyfile` to generate the document in `html/`.
3. Open `example/docs/html/index.html` with a browser.

### Editing example CUTB test scripts

The example CUTB test scripts are in `example/test/`.

If you try to add a test, add it to one of the existing test files or create a new file whose name ends with `_test.cpp` in the directory.

If you have added a new test file, add the file to the example solution in Visual Studio to run the test on Microsoft Unit Testing Framework.

About examples for POSIX, the wildcard function of GNU Make catches files whose name end with `_test.cpp` in `example/test/` and processes them automatically.



## Usage according to applications

### Boost Test Library

When you use Boost Test Library, use a CUTB configuration header (cutb_config.h) that includes `cutb/bridge/boosttest.h`.

See `example/runner/boosttest` for an example of Boost Test Library usage.

In Ubuntu, you can install Boost Test Library via:
```
sudo apt install libboost-test-dev
```

### Microsoft Unit Testing Framework

When you use Microsoft Unit Testing Framework, use a CUTB configuration header (cutb_config.h) that includes `cutb/bridge/msvc.h`.

See `example/runner/msvc` for an example of a Visual Studio project to run tests.

Note that there might be name conflicts with your program because this framework uses macros that have names such as TEST_METHOD and TEST_CLASS.

Note also that Microsoft Unit Testing Framework for C++ did not exist until Visual Studio 2012.

As a side note, Visual Studio has caused the semicolon following CUTB_TEST_GROUP_END.
An implementation that makes the macro, namely CUTB_TEST_GROUP_END, include the semicolon was tried, but it caused a problem in Visual Studio 2015, which was that a breakpoint set to a line of an assertion often did not stop debugger execution.

#### Restriction
In the document window, you cannot run or debug just one test by using shortcut keys or the right click menu.
To run or debug just one test, right click a test in the Test Explorer window.


### Using the parser

By using the CUTB parser, you can make a program that processes information about test groups in test files and tests in the test groups.

When you use the parser, use a CUTB configuration header (cutb_config.h) that includes `cutb/parser/cutb_parse_config.h`.
You also need to compile and link `src/cutb_parser_core.cpp`.

See [the Doxygen documentation](https://wakairo.github.io/cutb-doxydocs/classcutb_1_1_parser.html) for the available API.

See the following wrapper for an example of the parser usage, because the wrapper uses the parser.

### Using the wrapper

By using the CUTB parser, the CUTB wrapper wraps tests.
The wrapped tests can be executed by Google Test and Cpputest.
The wrapper also generates code for helper functions for language C use.

The source code about wrapper is gathered in `wrapper/`.

To build and execute the wrapper, execute `make` in `example/wrapper/`.


### Google Test

In order to use Google Test, you need to wrap your tests first.
When you compile the wrapped tests for Google Test, use a CUTB configuration header (cutb_config.h) that includes `cutb/bridge/gtest.h`.

See `example/runner/gtest` for an example of Google Test usage.

See [the github repository](https://github.com/google/googletest) for more information about Google Test.

Note that there might be name conflicts with your program because this framework uses macros that have names such as TEST, FAIL, SUCCEED, and ASSERT_EQ.
When the conflict occurs, rename the macros by following the instructions of [this page](https://github.com/google/googletest/blob/master/googletest/docs/FAQ.md#google-test-defines-a-macro-that-clashes-with-one-defined-by-another-library-how-do-i-deal-with-that).
If you change a name of a macro used in `cutb/bridge/gtest.h`, change the name in the header file.

### Cpputest

In order to use Cpputest, you need to wrap your tests first.
When you compile the wrapped tests for Cpputest, use a CUTB configuration header (cutb_config.h) that includes `cutb/bridge/cpputest.h`.

See `example/runner/cpputest` for an example of Cpputest usage.

See [this page](http://cpputest.github.io/) for more information, such as installation instructions, about Cpputest.

The version of Cpputest used with CUTB must be 3.6 or later.

In Ubuntu 16.04, you can install Cpputest later than 3.6 by the following command, but in Ubuntu 14.04, which is the previous LTS, the version to be installed is older than 3.6.
```
sudo apt install cpputest
```

Note that there might be name conflicts with your program because this framework uses macros that have names such as TEST, TEST_GROUP, and CHECK

#### Restriction
When you use Cpputest, the same name for multiple test groups, even in different test files, causes an error.


### CUTB simplified unit testing framework

When you use the simplified unit testing framework, select a type of framework and a type of assertion in the CUTB configuration header (cutb_config.h).
You can use all combinations of type of framework and type of assertion.

In any combination, when an assertion fails, the test execution is terminated at the assertion. The next test is not automatically executed. Also, there is no feature that resumes execution of tests after a runtime error, such as zero division error.

The purpose of this simplified unit testing framework is allowing unit tests to run in restricted environment, such as a target machine (a real device) in cross development for embedded software.
Therefore, this framework does not rely on any operating system and uses few features of the standard C or C++ library. Also, the code size is small. However, the other side of these advantages is that this framework has very few features, which are realized in the restriction. Hence, use this simplified unit testing framework only when there is a problem that is difficult for the other testing frameworks to solve.

As a side note, in a restricted environment, imposed requirements sometimes include use of an old compiler, so the simplified unit testing framework has been implemented in a way that allows compilation under C++03.


#### Types of frameworks

##### Simple type

The simple type framework allows you to execute tests one by one from the first test or from the test you indicate.

When you use this framework, make the CUTB configuration header (cutb_config.h) include `cutb/framework/simple.h`.
You also need to compile and link `src/cutb_framework_simple_core.cpp`.

See [the Doxygen documentation](https://wakairo.github.io/cutb-doxydocs/classcutb_1_1_test_manager.html) for the available API.

See `example/runner/simple` for an example of usage of this type of framework.

When an assertion fails or a runtime error occurs, the test execution is terminated at the assertion or at the error. Thus, to restart test execution from the next test, manual operation is needed.
In the example, a test number of each test is printed just before executing the test. Hence, you can restart test execution from the next test by starting the example test runner with the next test number as its argument.

Because there is API to get test names, etc., you can write a program that starts test execution from the test with a specific name, etc.

##### Minimum type in C++ (mincpp type)

The mincpp type framework calls tests using static object constructors.
Thus, the order of calling tests is the same as the order of calling static object constructors.
Therefore, it is impossible to dynamically change the order or to start from an arbitrary test. Moreover, there is neither a API class nor a API function.

Note that the standard library or a user library might have static objects that must be initialized before calling tests. Be careful of the static initialization order fiasco.
For example, if you use a standard I/O stream object, such as `cout`, in your unit test, you need to initialize the stream object before calling the test by using `std::ios_base::Init`, etc. correctly.

In conclusion, you should **use the simple type instead of the mincpp type as much as possible**.
An assumed use case of mincpp is only when you really need to reduce the amount of code for calling unit tests.

When you use mincpp type framework, make the CUTB configuration header (cutb_config.h) include `cutb/framework/mincpp.h`.

See `example/runner/mincpp` for an example of usage of this type of framework.

##### Language C type (langc type)

Even when a compiler for a target machine does not support C++ in cross development, you can compile your tests only in C and run the tests on the target machine by using the wrapper and this type of framework.
In this case, the wrapper runs on a host development machine because it uses C++.
After the wrapping, the wrapped tests can be compiled only in C.

Note that you must write both your unit tests and your program to be tested only in C to compile them only in C.

When you compile the wrapped tests for langc type framework, make the CUTB configuration header (cutb_config.h) include `cutb/framework/langc.h`.

See [the Doxygen documentation](https://wakairo.github.io/cutb-doxydocs/chelper_8h.html) for the available API.

See `example/runner/langc` for an example of usage of this type of framework.


#### Types of assertions

##### Assertions using exit()

When an assertion fails, fprintf() outputs an error message to the standard error output, and exit() terminates the program.

When you use assertions using exit(), use a CUTB configuration header (cutb_config.h) that includes `cutb/assert/exit.h`.
You also need to compile and link `src/cutb_assert_exit.cpp`.

See `example/runner/simple` for an example of usage of this type of assertions.

##### Assertions using the standard assert macro

When you use assertions using the assert macro in the C standard library, use a CUTB configuration header (cutb_config.h) that includes `cutb/assert/std.h`.

See `example/runner/mincpp` for an example of usage of this type of assertions.

The advantage of using this type of assertions is that the requirements on a test execution environment are only assert().
The disadvantage is that if the macro NDEBUG is defined in the release build or something, assert() is invalidated, so the unit tests do not work.
(The C standard defines the effect of NDEBUG on assert().)


### Other applications than executing tests

#### Generating test documentation with Doxygen

It is possible to make Doxygen generate test documentation by setting up a Doxygen configuration file (Doxyfile).
The key configuration is the PREDEFINED tag.
By setting PREDEFINED tag appropriately, you can expand CUTB test macros into a suitable expression for generating test documentation. For example, it is possible to make Doxygen recognize test groups as namespaces and tests as functions.

See `example/docs/` for a test documentation example.
If you change directory to `example/docs/` and execute the following command,  the HTML documentation of the tests in `example/test/` is generated.
Open `example/docs/html/index.html` with a browser to read the documentation.

```
doxygen Doxyfile
```

In Ubuntu, you can install Doxygen via:
```
sudo apt install doxygen
```

#### Measuring coverage (Confirming execution of tests)

If you use one of GCC compilers, you can check coverage with gcov.
Since the coverage result shows you which lines are executed, you can confirm that each test is executed.

To see an example of coverage,
1. change directory to one of the directories in `example/runner/`, such as `example/runner/simple/`,
2. execute `make test` to run tests, and
3. execute `gcov *.gcda` to output the coverage result to files that have the file extension `.gcov`.

If you check branch coverage in addition to statement coverage, give `-b` option and execute `gcov -b *.gcda`.

See gcov's manual for more details.
