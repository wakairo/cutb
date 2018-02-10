#ifndef CUTB_EXCEPTIONS_H
#define CUTB_EXCEPTIONS_H

#include <stdexcept>

namespace cutb {

class Exception : public std::runtime_error {
public:
    Exception(const std::string &what) : std::runtime_error(what) {}
};

class ArgumentError : public Exception {
public:
    ArgumentError(const std::string &what) : Exception(what) {}
};
}

#endif
