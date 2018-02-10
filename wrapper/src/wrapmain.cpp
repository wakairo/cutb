#include <unistd.h>

#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "cutb/parser/core.h"
#include "cutb/utils/filepath.h"

#define CUTB_I_WRAPPER_ARGUMENTS_USAGE                                         \
    " [-s suffix] [-p prefix] [-a] [-c c-helper-file-name] "                   \
    "[file-to-be-wrapped]..."
/*
 * The wrapper wraps the test files whose names are in FILE-TO-BE-WRAPPEDs.
 *
 * ## Options
 * -s SUFFIX
 *     Add SUFFIX to names of wrapped test files.
 * -p PREFIX
 *     Add PREFIX to names of wrapped test files.
 * -a
 *     Generate all wrapped test files.
 * -c C-HELPER-FILE-NAME
 *     Generate code of C helper in a file with name of C-HELPER-FILE-NAME.
 */

namespace {

using std::size_t;
typedef cutb::Parser::TestDef TestDef;
typedef cutb::Parser::TestGrp TestGrp;
typedef cutb::Parser::TestFile TestFile;

class Options {
private:
    size_t npaths_;
    const char *const *paths_;
    std::string prefix_;
    std::string suffix_;
    bool is_all_tests_;
    std::string c_helper_file_name_;

public:
    size_t npaths() { return npaths_; }
    const char *const *paths() { return paths_; }
    const std::string &prefix() { return prefix_; }
    const std::string &suffix() { return suffix_; }
    bool isAllTests() { return is_all_tests_; }
    const std::string &cHelperFileName() { return c_helper_file_name_; }
public:
    Options(int argc, char *argv[])
        : npaths_(0), paths_(NULL), prefix_(), suffix_(), is_all_tests_(false),
          c_helper_file_name_()
    {
        int opt;
        while (-1 != (opt = getopt(argc, argv, "ac:p:s:"))) {
            switch (opt) {
            case 'a':
                is_all_tests_ = true;
                break;
            case 'c':
                c_helper_file_name_.assign(optarg);
                break;
            case 'p':
                prefix_.assign(optarg);
                break;
            case 's':
                suffix_.assign(optarg);
                break;
            default:
                /* getopt() returns '?' or ':' on errors. */
                /* For more details, see the manual of getopt(). */
                std::ostringstream oss;
                oss << "usage: " << argv[0] << CUTB_I_WRAPPER_ARGUMENTS_USAGE;
                throw cutb::Exception(oss.str());
                break;
            }
        }
        if (argc > optind) {
            npaths_ = argc - optind;
            paths_ = &argv[optind];
        }
    }
};

class WrappedTestFileWriter : public cutb::Parser {
private:
    std::string prefix_;
    std::string suffix_;
    std::ofstream os_;

public:
    WrappedTestFileWriter(const std::string &prefix, const std::string &suffix)
        : prefix_(prefix), suffix_(suffix), os_()
    {
    }
    virtual void at(const TestDef *testdef, const TestGrp *grp,
                    const TestFile *file)
    {
        os_ << "CUTB_I_WRAPPED_TEST(" << grp->grpname() << ", "
            << testdef->testname() << ")" << std::endl;
        os_ << "{" << std::endl;
        os_ << "    CUTB_I_WRAPPER_TEST_ID(" << grp->grpname() << ", "
            << testdef->testname() << ", " << testdef->lineno() << ")();"
            << std::endl;
        os_ << "}" << std::endl;
    }
    virtual void start(const TestGrp *grp, const TestFile *file)
    {
        os_ << "CUTB_I_WRAPPED_TEST_GROUP(" << grp->grpname() << ")"
            << std::endl;
    }
    virtual void start(const TestFile *file)
    {
        cutb::utils::FilePath fp(file->filepath());
        const char *const fname = fp.filename_ptr();
        if (NULL == fname) {
            std::ostringstream oss;
            oss << "error: no file name in the test file path '"
                << file->filepath() << "'";
            throw cutb::Exception(oss.str());
        }

        const std::string path = prefix_ + fname + suffix_;
        os_.open(path.c_str());
        if (!os_) {
            std::ostringstream oss;
            oss << "error: unable to open wrap file '" << path
                << "': " << std::strerror(errno);
            throw cutb::Exception(oss.str());
        }
        os_ << "#include " << '"' << "cutb/wrapper/cutb_wrap_config.h" << '"'
            << std::endl;
        os_ << "#include " << '"' << file->filepath() << '"' << std::endl;
    }
    virtual void end(const TestFile *file) { os_.close(); }
};

void writeChelperTestID(std::ofstream &os, const TestGrp *grp,
                        const TestDef *testdef)
{
    os << "CUTB_I_CHELPER_TEST_ID(" << grp->grpname() << ", "
       << testdef->testname() << ")";
}

class CProxyDeclarationsWriter : public cutb::Parser {
private:
    std::ofstream &os_;

public:
    CProxyDeclarationsWriter(std::ofstream &os) : os_(os) {}
    virtual void at(const TestDef *testdef, const TestGrp *grp,
                    const TestFile *file)
    {
        os_ << "extern void ";
        writeChelperTestID(os_, grp, testdef);
        os_ << "();" << std::endl;
    }
    virtual void start(const TestFile *file)
    {
        os_ << "/* File: " << file->filepath() << " */" << std::endl;
    }
};

class CRunnerWriter : public cutb::Parser {
private:
    static const char kHeadPart[];
    static const char kTailPart[];

private:
    std::ofstream &os_;
    size_t count_;

public:
    size_t count() { return count_; }
    CRunnerWriter(std::ofstream &os) : os_(os), count_(0) { os_ << kHeadPart; }
    ~CRunnerWriter() { os_ << kTailPart; }
    virtual void at(const TestDef *testdef, const TestGrp *grp,
                    const TestFile *file)
    {
        os_ << "    case " << count_ << ":" << std::endl;
        os_ << "        ";
        writeChelperTestID(os_, grp, testdef);
        os_ << "();" << std::endl;
        os_ << "        break;" << std::endl;
        ++count_;
    }
    virtual void start(const TestFile *file)
    {
        os_ << "    /* File: " << file->filepath() << " */" << std::endl;
    }
};
const char CRunnerWriter::kHeadPart[] = "void cutb_run_test(size_t idx)\n"
                                        "{\n"
                                        "    switch (idx) {\n";
const char CRunnerWriter::kTailPart[] =
    "    default:\n"
    "        assert(NULL != \"Invalid test index\");\n"
    "        break;\n"
    "    }\n"
    "}\n";

void writeCHelperCode(const char *path)
{
    static const char kHeadPart[] =
        "#include <assert.h>\n"
        "#include <stddef.h>\n"
        "\n"
        "#include \"cutb/wrapper/chelper/cmndef.h\"\n"
        "#include \"cutb/wrapper/chelper.h\"\n";
    static const char kTailPart[] = "size_t cutb_ntests(void)\n"
                                    "{\n"
                                    "    return CUTB_I_CHELPER_N_TESTS;\n"
                                    "}\n";

    std::ofstream os(path);
    if (!os) {
        std::ostringstream oss;
        oss << "error: unable to open C helper file '" << path
            << "': " << std::strerror(errno);
        throw cutb::Exception(oss.str());
    }
    os << kHeadPart << std::endl;
    {
        CProxyDeclarationsWriter wtr(os);
        cutb::Parser::parse(wtr);
    }
    os << std::endl;
    size_t ntests;
    {
        CRunnerWriter wtr(os);
        cutb::Parser::parse(wtr);
        ntests = wtr.count();
    }
    os << std::endl;
    os << "#define CUTB_I_CHELPER_N_TESTS " << ntests << "\n";
    os << std::endl;
    os << kTailPart;
}
}

int main(int argc, char *argv[])
{
    try {
        Options opts(argc, argv);

        WrappedTestFileWriter wtfw(opts.prefix(), opts.suffix());
        if (opts.isAllTests()) {
            cutb::Parser::parse(wtfw);
        } else {
            for (size_t i = 0; i < opts.npaths(); ++i) {
                try {
                    cutb::Parser::parse(wtfw, opts.paths()[i]);
                } catch (const cutb::ArgumentError &) {
                    std::ostringstream oss;
                    oss << "error: unkonwn test file path '" << opts.paths()[i]
                        << "'";
                    throw cutb::Exception(oss.str());
                }
            }
        }

        const std::string &c_helper_file_name = opts.cHelperFileName();
        if (!c_helper_file_name.empty()) {
            writeCHelperCode(c_helper_file_name.c_str());
        }
    } catch (const cutb::Exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
