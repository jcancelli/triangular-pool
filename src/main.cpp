#include <SFML/Graphics.hpp>
#include <iostream>

#include "arguments.hpp"
#include "graphics/window.hpp"
#include "simulation.hpp"

int main(int argc, char* argv[]) {
  try {
    Config config;

    switch (parseArguments(argc, argv, config)) {
      case ParseStatus::HelpShown:
        return EXIT_SUCCESS;
      case ParseStatus::Error:
        return EXIT_FAILURE;
      default:
        // do nothing, keep going
        break;
    }

    Simulation simulation(config.r1, config.r2, config.l, config.meanInitialY,
                          config.stddevInitialY, config.meanInitialTheta,
                          config.stddevInitialTheta);

    if (config.graphics) {
      GraphicsWindow window(700, 700, simulation);
      window.show();
    } else {
      for (int i = 0; i < config.iterations; i++) {
        simulation.newIteration();
        simulation.immediate();
      }
    }
  } catch (std::exception const& e) {
    std::cout << "Unexpected error\n";
    std::cout << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cout << "Unknown error\n";
    return EXIT_FAILURE;
  }
}