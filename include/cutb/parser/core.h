#ifndef CUTB_PARSER_CORE_H
#define CUTB_PARSER_CORE_H

#include <cstddef>
#include <list>

#include "cutb/exceptions.h"

/** @file
 * API for parsing CUTB tests.
 */

namespace cutb {

/**
 * API class for parsing CUTB tests.
 *
 * To parse tests, first define a subclass of Parser overriding callback
 * functions, and then call parse() with an object of the subclass.
 * Not all the callback functions need to be overridden.
 */
class Parser {
public:
    class TestFile;
    class TestGrp;
    class TestDef;

    /**
     * Parses all test files.
     *
     * @param parser an object of a subclass of Parser
     */
    static void parse(Parser &parser);
    /**
     * Parses a test file.
     *
     * @param parser an object of a subclass of Parser
     * @param filepath the file path to the test file to be parsed
     */
    static void parse(Parser &parser, const char *filepath);

    /**
     * The callback function called at the start of each file
     *
     * @param file file information
     */
    virtual void start(const TestFile *file) {}
    /**
     * The callback function called at the end of each file
     *
     * @param file file information
     */
    virtual void end(const TestFile *file) {}
    /**
     * The callback function called at the start of each test group
     *
     * @param grp test group information
     * @param file file information
     */
    virtual void start(const TestGrp *grp, const TestFile *file) {}
    /**
     * The callback function called at the end of each test group
     *
     * @param grp test group information
     * @param file file information
     */
    virtual void end(const TestGrp *grp, const TestFile *file) {}
    /**
     * The callback function called at each test definition
     *
     * @param testdef test definition information
     * @param grp test group information
     * @param file file information
     */
    virtual void at(const TestDef *testdef, const TestGrp *grp,
                    const TestFile *file)
    {
    }

    Parser() : file_(NULL), grp_(NULL) {}
    virtual ~Parser() = 0;

private:
    const TestFile *file_;
    const TestGrp *grp_;

    void traverseTestdefs(const TestGrp *grp);
    void traverseTestgrps(const TestFile *file);
    void operator()(const TestDef *testdef);
    void operator()(const TestGrp *grp);
    void operator()(const TestFile *file);

    static void addTest(TestGrp *grp, const TestDef *testdef);
    static void addGrp(TestFile *file, const TestGrp *grp);

public:
    /**
     * Test definition
     */
    class TestDef {
    public:
        /** @returns the test name. */
        const char *testname() const { return testname_; }
        /** @returns the line number of the test. */
        int lineno() const { return lineno_; }
        TestDef(const char *testname, const char *filepath, int lineno);

    private:
        const char *const testname_;
        const int lineno_;
    };
    /**
     * Test group
     */
    class TestGrp {
    public:
        /** @returns the test group name. */
        const char *grpname() const { return grpname_; }
        /** @returns the line number of the test group. */
        int lineno() const { return lineno_; }
        TestGrp(const char *grpname, const char *filepath, int lineno);

    private:
        typedef std::list<const TestDef *> ListTestdef;
        ListTestdef list_;
        const char *const grpname_;
        const int lineno_;
        friend void Parser::addTest(TestGrp *grp, const TestDef *testdef);
        friend void Parser::traverseTestdefs(const TestGrp *grp);
    };

    /**
     * Test file
     */
    class TestFile {
    public:
        /** @returns the file path to the test file. */
        const char *filepath() const { return filepath_; }
        TestFile(const char *filepath) : list_(), filepath_(filepath) {}
    private:
        typedef std::list<const TestGrp *> ListTestgrp;
        ListTestgrp list_;
        const char *const filepath_;
        friend void Parser::addGrp(TestFile *file, const TestGrp *grp);
        friend void Parser::traverseTestgrps(const TestFile *file);
    };

    class TestGrpEnd {
    public:
        TestGrpEnd(const char *filepath, int lineno);
    };
};
}

#endif
