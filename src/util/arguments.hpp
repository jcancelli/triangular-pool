#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include "config.hpp"

namespace pool {

namespace util {

enum class ParseStatus { Success, Error, HelpShown };

ParseStatus parseArguments(int argc, char* argv[], Config& config);

}  // namespace util

}  // namespace pool

#endif