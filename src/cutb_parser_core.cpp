#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "cutb/parser/core.h"

namespace {

void handle_test_load_error(const char *filepath, int lineno, const char *msg)
{
    static std::ios_base::Init object_to_ensure_standard_stream_initialization;

    std::cerr << filepath << ':' << lineno << ':' << " error: " << msg
              << std::endl;
    exit(EXIT_FAILURE);
    return;
}

struct Context {
    cutb::Parser::TestFile testfile;
    cutb::Parser::TestGrp *testgrp;
    Context(cutb::Parser::TestFile const &tfile, cutb::Parser::TestGrp *tgrp)
        : testfile(tfile), testgrp(tgrp)
    {
    }
};

typedef std::map<const std::string, Context> Contexts;

Contexts &contexts()
{
    static Contexts obj;
    return obj;
}

cutb::Parser::TestFile *grpBegin(const char *filepath, int lineno,
                                 cutb::Parser::TestGrp *testgrp)
{
    Contexts &cs = contexts();
    const std::string str(filepath);
    Contexts::iterator it = cs.find(str);
    if (it != cs.end()) {
        if (NULL != it->second.testgrp) {
            handle_test_load_error(filepath, lineno,
                                   "beginning of the new group "
                                   "before ending of the previous group");
        }
        it->second.testgrp = testgrp;
        return &(it->second.testfile);
    } else {
        std::pair<Contexts::iterator, bool> pr = cs.insert(std::make_pair(
            str, Context(cutb::Parser::TestFile(filepath), testgrp)));
        assert(pr.second);
        return &(pr.first->second.testfile);
    }
}

void grpEnd(const char *filepath, int lineno)
{
    Contexts &cs = contexts();
    const std::string str(filepath);
    Contexts::iterator it = cs.find(str);
    if (it == cs.end()) {
        handle_test_load_error(filepath, lineno, "extraneous group ending");
    }
    it->second.testgrp = NULL;
}

cutb::Parser::TestGrp *getCurGrp(const char *filepath, int lineno)
{
    Contexts &cs = contexts();
    const std::string str(filepath);
    Contexts::iterator it = cs.find(str);
    if (it == cs.end()) {
        handle_test_load_error(filepath, lineno, "test not in any group");
    }
    return it->second.testgrp;
}
}

namespace cutb {

void Parser::parse(Parser &parser)
{
    const Contexts &cs = contexts();
    for (Contexts::const_iterator it = cs.begin(); it != cs.end(); ++it) {
        parser(&(it->second.testfile));
    }
}

void Parser::parse(Parser &parser, const char *filepath)
{
    const Contexts &cs = contexts();
    const std::string str(filepath);
    Contexts::const_iterator it = cs.find(str);
    if (it == cs.end()) {
        throw ArgumentError(std::string());
    }
    parser(&(it->second.testfile));
}

Parser::~Parser()
{
}

void Parser::traverseTestgrps(const TestFile *file)
{
    for (TestFile::ListTestgrp::const_iterator it = file->list_.begin();
         it != file->list_.end(); ++it) {
        (*this)(*it);
    }
}

void Parser::operator()(const TestDef *testdef)
{
    at(testdef, grp_, file_);
}

void Parser::traverseTestdefs(const TestGrp *grp)
{
    for (TestGrp::ListTestdef::const_iterator it = grp->list_.begin();
         it != grp->list_.end(); ++it) {
        (*this)(*it);
    }
}

void Parser::operator()(const TestGrp *grp)
{
    grp_ = grp;
    start(grp, file_);
    traverseTestdefs(grp);
    end(grp, file_);
}

void Parser::operator()(const TestFile *file)
{
    file_ = file;
    start(file);
    traverseTestgrps(file);
    end(file);
}

void Parser::addTest(TestGrp *grp, const TestDef *testdef)
{
    grp->list_.push_back(testdef);
}

Parser::TestDef::TestDef(const char *testname, const char *filepath, int lineno)
    : testname_(testname), lineno_(lineno)
{
    addTest(getCurGrp(filepath, lineno), this);
}

void Parser::addGrp(TestFile *file, const TestGrp *grp)
{
    file->list_.push_back(grp);
}

Parser::TestGrp::TestGrp(const char *grpname, const char *filepath, int lineno)
    : list_(), grpname_(grpname), lineno_(lineno)
{
    TestFile *file = grpBegin(filepath, lineno, this);
    addGrp(file, this);
}

Parser::TestGrpEnd::TestGrpEnd(const char *filepath, int lineno)
{
    grpEnd(filepath, lineno);
}
}
