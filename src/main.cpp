#include <SFML/Graphics.hpp>
#include <iostream>

#include "graphics/font.hpp"
#include "graphics/window.hpp"
#include "math/angles.hpp"
#include "simulation.hpp"
#include "util/arguments.hpp"

namespace pool {

int main(int argc, char* argv[]) {
  try {
    util::Config config;

    switch (parseArguments(argc, argv, config)) {
      case util::ParseStatus::HelpShown:
        return EXIT_SUCCESS;
      case util::ParseStatus::Error:
        return EXIT_FAILURE;
      default:
        // do nothing, keep going
        break;
    }

    graphics::loadFonts();  // throws runtime_error if unable to find a font file

    Simulation simulation(config.r1, config.r2, config.l, config.meanInitialY,
                          config.stddevInitialY, math::radians(config.meanInitialTheta),
                          math::radians(config.stddevInitialTheta));
    simulation.setVerboseOutput(config.verboseOutput);
    simulation.setSpeedMultiplier(config.simulationSpeed);

    if (config.graphics) {
      graphics::GraphicsWindow window(simulation);
      window.show();
    } else {
      for (int i = 0; i < config.iterations; i++) {
        simulation.newIteration();
        simulation.immediate();
      }
      std::cout << "\n------ Stats ------\n" << simulation.getStats() << "\n";
    }
  } catch (std::runtime_error const& e) {
    std::cout << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (std::exception const& e) {
    std::cout << "Unexpected error\n";
    std::cout << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cout << "Unknown error\n";
    return EXIT_FAILURE;
  }
}

}  // namespace pool