#ifndef CONFIG_HPP
#define CONFIG_HPP

struct Config {
  bool graphics = false;
  bool verboseOutput = false;
  double r1 = 2.0;
  double r2 = 1.0;
  double l = 5.0;
  int iterations = 1;
  double meanInitialY = 0.0;
  double stddevInitialY = 1.0;
  double meanInitialTheta = 0.0;
  double stddevInitialTheta = 1.0;
};

void validateConfig(Config const& config);

#endif