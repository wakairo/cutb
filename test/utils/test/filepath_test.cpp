#include "cutb_config.h"

#include <cstring>
#include <string>

#include "cutb/utils/filepath.h"

namespace {

void checkfp_part(const char *expected_ptr, const char *actual_ptr,
                  size_t actual_size)
{
    if (NULL == expected_ptr) {
        CUTB_ASSERT_EQ_ULONG(0, actual_size);
        CUTB_ASSERT(NULL == actual_ptr);
    } else {
        const size_t expected_size = strlen(expected_ptr);
        CUTB_ASSERT_EQ_ULONG(expected_size, actual_size);
        CUTB_ASSERT(NULL != actual_ptr);
        CUTB_ASSERT(0 == std::strncmp(expected_ptr, actual_ptr, expected_size));
    }
}

void checkfp(const char *path, const char *expected_parent,
             const char *expected_stem, const char *expected_extension)
{
    cutb::utils::FilePath fp(path);
    checkfp_part(expected_parent, fp.parent_ptr(), fp.parent_size());
    checkfp_part(expected_stem, fp.stem_ptr(), fp.stem_size());
    checkfp_part(expected_extension, fp.extension_ptr(), fp.extension_size());

    const char *expected_filename = NULL;
    std::string filename;
    if (NULL != expected_stem || NULL != expected_extension) {
        if (NULL != expected_stem) {
            filename.assign(expected_stem);
        }
        if (NULL != expected_extension) {
            filename.append(expected_extension);
        }
        expected_filename = filename.c_str();
    }
    checkfp_part(expected_filename, fp.filename_ptr(), fp.filename_size());
}
}

CUTB_TEST_GROUP(FilepathTest)

CUTB_TEST(NullTest)
{
    checkfp(NULL, NULL, NULL, NULL);
}

CUTB_TEST(AbsolutePathTest)
{
    checkfp("/foobar/foo/bar.baz", "/foobar/foo/", "bar", ".baz");
}

CUTB_TEST(RelativePathTest)
{
    checkfp("../foo/bar.baz", "../foo/", "bar", ".baz");
}

CUTB_TEST(MultipleSlashesAndDotsTest)
{
    checkfp("//f.o..o//b.a.r..baz", "//f.o..o//", "b.a.r.", ".baz");
}

CUTB_TEST(DotBeforeSlashTest)
{
    checkfp("f.oo/bar", "f.oo/", "bar", NULL);
}

CUTB_TEST(SingleSlashTest)
{
    checkfp("/", "/", NULL, NULL);
}

CUTB_TEST(SingleDotTest)
{
    checkfp(".", NULL, NULL, ".");
}

CUTB_TEST(SlashStemTest)
{
    checkfp("/a", "/", "a", NULL);
}

CUTB_TEST(SlashStemDotTest)
{
    checkfp("/a.", "/", "a", ".");
}

CUTB_TEST(StemDotTest)
{
    checkfp("a.", NULL, "a", ".");
}

CUTB_TEST(SlashDotTest)
{
    checkfp("/.", "/", NULL, ".");
}

CUTB_TEST(DotSlashTest)
{
    checkfp("./", "./", NULL, NULL);
}

CUTB_TEST(SlashExtensionTest)
{
    checkfp("/.baz", "/", NULL, ".baz");
}

CUTB_TEST(ParentDotTest)
{
    checkfp("foo/.", "foo/", NULL, ".");
}

CUTB_TEST(CombinationTestPSE)
{
    checkfp("foo/bar.baz", "foo/", "bar", ".baz");
}

CUTB_TEST(CombinationTestPS0)
{
    checkfp("foo/bar", "foo/", "bar", NULL);
}

CUTB_TEST(CombinationTestP0E)
{
    checkfp("foo/.baz", "foo/", NULL, ".baz");
}

CUTB_TEST(CombinationTestP00)
{
    checkfp("foo/", "foo/", NULL, NULL);
}

CUTB_TEST(CombinationTest0SE)
{
    checkfp("bar.baz", NULL, "bar", ".baz");
}

CUTB_TEST(CombinationTest0S0)
{
    checkfp("bar", NULL, "bar", NULL);
}

CUTB_TEST(CombinationTest00E)
{
    checkfp(".baz", NULL, NULL, ".baz");
}

CUTB_TEST(CombinationTest000)
{
    checkfp("", NULL, NULL, NULL);
}

CUTB_TEST_GROUP_END;
