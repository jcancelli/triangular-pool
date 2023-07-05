#ifndef CONFIG_HPP
#define CONFIG_HPP

enum class GraphicalMode { Text, Graphic };

struct Config {
  GraphicalMode mode = GraphicalMode::Text;
  double r1 = 2.0;
  double r2 = 1.0;
  double l = 5.0;
  int iterations = 1;
  double meanInitialY = 0.0;
  double stddevInitialY = 1.0;
  double meanInitialTheta = 0.0;
  double stddevInitialTheta = 1.0;
};

#endif