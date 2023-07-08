#include "config.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace pool {

namespace util {

void validateConfig(Config const& config) {
  if (config.r1 < 0) {
    throw std::invalid_argument("Error: R1 can't be negative.");
  }
  if (config.r2 < 0) {
    throw std::invalid_argument("Error: R2 can't be negative.");
  }
  if (config.l < 0) {
    throw std::invalid_argument("Error: L can't be negative.");
  }
  if (config.iterations < 1) {
    throw std::invalid_argument("Error: N can't be less than 1.");
  }
  if (config.meanInitialY > config.r1) {
    throw std::invalid_argument("Error: mean-y can't be more than R1.");
  }
  if (config.meanInitialY < -config.r1) {
    throw std::invalid_argument("Error: mean-y can't be less than -R1.");
  }
  if (config.stddevInitialY < 0) {
    throw std::invalid_argument("Error: std-dev-y can't be negative.");
  }
  if (config.meanInitialTheta > 90) {
    throw std::invalid_argument("Error: mean-theta can't be more than 90°.");
  }
  if (config.meanInitialTheta < -90) {
    throw std::invalid_argument("Error: mean-theta can't be less than -90°.");
  }
  if (config.stddevInitialTheta < 0) {
    throw std::invalid_argument("Error: std-dev-theta can't be negative.");
  }
  if (config.simulationSpeed <= 0) {
    throw std::invalid_argument("Error: speed must be a positive number.");
  }
  if (config.graphics && config.iterations > 1) {
    std::cout << "Warning: since graphic mode is on, the parameter --n (number of iterations) will "
                 "be ignored.\n";
  }
  if (config.graphics && config.verboseOutput) {
    std::cout << "Warning: since graphic mode is on, the parameter --verbose will be ignored.\n";
  }
  if (!config.graphics && config.simulationSpeed != 1.0) {
    std::cout << "Warning: since graphic mode is off, the parameter --speed will be ignored.\n";
  }
}

}  // namespace util

}  // namespace pool