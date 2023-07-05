#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include "config.hpp"

enum class ParseStatus { Success, Error, HelpShown };

ParseStatus parseArguments(int argc, char* argv[], Config& config);

#endif