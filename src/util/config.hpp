#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace pool {

namespace util {

struct Config {
  bool graphics = false;
  bool verboseOutput = false;
  bool outputAsCSV = false;
  bool outputCSVHeaders = false;
  double r1 = 2.0;
  double r2 = 1.0;
  double l = 5.0;
  int iterations = 1;
  double meanInitialY = 0.0;
  double stddevInitialY = 1.0;
  double meanInitialTheta = 0.0;
  double stddevInitialTheta = 10.0;
  double simulationSpeed = 1.0;
};

void validateConfig(Config const& config);

}  // namespace util

}  // namespace pool

#endif