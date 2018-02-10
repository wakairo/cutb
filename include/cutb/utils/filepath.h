#ifndef CUTB_UTILS_FILEPATH_H
#define CUTB_UTILS_FILEPATH_H

#include <cassert>
#include <cstddef>

/** @file
 * File path utility
 */

namespace cutb {
namespace utils {

/**
 * An object of this class analyzes a path string and gives information about
 * its parent path, stem, and extension. This class does a rough analysis,
 * using the last slash and the last dot in the path string.
 *
 * In this class,
 * - the parent path is the last slash and the part preceding the last slash,
 * - the extension is the last dot and the part following the dot, and
 * - the stem is the part between the last slash and the dot.
 *
 * For example, "../foo/bar.baz" is split into
 * the parent path of "../foo/", the stem of "bar", and the extension of ".baz".
 *
 * This analysis does not work correctly for special paths such as
 * dot (".") or dot-dot ("..").
 *
 * @note
 * std::filesystem::path should be used instead of this class if it is possible.
 */
class FilePath {
private:
    const char *const path_;
    size_t parent_size_;
    size_t stem_size_;
    size_t extension_size_;

public:
    /**
     * Constructs a new file path object from the parameter.
     *
     * @param path a null-terminated string of a file path
     */
    FilePath(const char *const path)
        : path_(path), parent_size_(0U), stem_size_(0U), extension_size_(0U)
    {
        if (NULL == path) {
            return;
        }
        const char *last_slash_pos = NULL;
        const char *last_dot_pos = NULL;
        const char *c = path_;
        while ('\0' != *c) {
            if ('/' == *c) {
                last_slash_pos = c;
            } else if ('.' == *c) {
                last_dot_pos = c;
            }
            ++c;
        }

        const char *const null_pos = c;
        if (NULL != last_slash_pos) {
            parent_size_ = (last_slash_pos - path_) + 1;
            if (NULL != last_dot_pos && last_slash_pos < last_dot_pos) {
                extension_size_ = null_pos - last_dot_pos;
            }
        } else {
            if (NULL != last_dot_pos) {
                extension_size_ = null_pos - last_dot_pos;
            }
        }

        const size_t path_size = null_pos - path_;
        assert(path_size >= (parent_size_ + extension_size_));
        stem_size_ = path_size - (parent_size_ + extension_size_);
    }
    /**
     * Returns the parent path size.
     * If there is no parent path, zero is returned.
     *
     * @returns the parent path size or zero.
     */
    size_t parent_size() const { return parent_size_; }
    /**
     * Returns the stem size.
     * If there is no stem, zero is returned.
     *
     * @returns the stem size or zero.
     */
    size_t stem_size() const { return stem_size_; }
    /**
     * Returns the extension size.
     * If there is no extension, zero is returned.
     *
     * @returns the extension size or zero.
     */
    size_t extension_size() const { return extension_size_; }
    /**
     * Returns the filename size, which is stem size plus extension size.
     * If there is neither stem nor extension, zero is returned.
     *
     * @returns the filename size or zero.
     */
    size_t filename_size() const { return stem_size_ + extension_size_; }
    /**
     * Returns a pointer to a string of the parent path.
     * If there is no parent path, NULL is returned.
     *
     * @returns a pointer to the parent path or NULL.
     */
    const char *parent_ptr() const { return 0 == parent_size_ ? NULL : path_; }
    /**
     * Returns a pointer to a string of the stem.
     * If there is no stem, NULL is returned.
     *
     * @returns a pointer to the stem or NULL.
     */
    const char *stem_ptr() const
    {
        return 0 == stem_size_ ? NULL : path_ + parent_size_;
    }
    /**
     * Returns a pointer to a string of the extension.
     * If there is no extension, NULL is returned.
     *
     * @returns a pointer to the extension or NULL.
     */
    const char *extension_ptr() const
    {
        return 0 == extension_size_ ? NULL
                                    : path_ + (parent_size_ + stem_size_);
    }
    /**
     * Returns a pointer to a string of the filename, which is stem plus
     * extension.
     * If there is neither stem nor extension, NULL is returned.
     *
     * @returns a pointer to the filename or NULL.
     */
    const char *filename_ptr() const
    {
        return (0 == stem_size_ && 0 == extension_size_) ? NULL
                                                         : path_ + parent_size_;
    }
};
}
}

#endif
