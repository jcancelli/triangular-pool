#include <SFML/Graphics.hpp>
#include <iostream>

#include "graphics/font.hpp"
#include "graphics/window.hpp"
#include "math/angles.hpp"
#include "simulation.hpp"
#include "util/arguments.hpp"

static void printOutput(pool::Simulation const&, pool::util::Config const&);

int main(int argc, char* argv[]) {
  try {
    pool::util::Config config;

    switch (parseArguments(argc, argv, config)) {
      case pool::util::ParseStatus::HelpShown:
        return EXIT_SUCCESS;
      case pool::util::ParseStatus::Error:
        return EXIT_FAILURE;
      default:
        // do nothing, keep going
        break;
    }

    pool::graphics::loadFonts();  // throws runtime_error if unable to find a font file

    pool::Simulation simulation(config.r1, config.r2, config.l, config.meanInitialY,
                                config.stddevInitialY, pool::math::radians(config.meanInitialTheta),
                                pool::math::radians(config.stddevInitialTheta));
    simulation.setVerboseOutput(config.verboseOutput);
    simulation.setSpeedMultiplier(config.simulationSpeed);

    if (config.graphics) {
      pool::graphics::GraphicsWindow window(simulation);
      window.show();
    } else {
      for (int i = 0; i < config.iterations; i++) {
        simulation.newIteration();
        simulation.immediate();
      }
    }

    printOutput(simulation, config);

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

static void printOutput(pool::Simulation const& simulation, pool::util::Config const& config) {
  if (config.outputAsCSV) {
    if (config.outputCSVHeaders) {
      std::cout << "r1;r2;l;n;mean-y;mean-theta;mean-collisions;std-dev-y;std-dev-theta;skew-y;"
                   "skew-theta;flat-y;flat-theta;mean-initial-y;std-dev-initial-y;mean-initial-"
                   "theta;std-dev-initial-theta\n";
    }
    std::cout << simulation.getR1() << ";" << simulation.getR2() << ";" << simulation.getL() << ";"
              << simulation.getStats().asCSV() << ";" << simulation.getMeanInitialParticleY() << ";"
              << simulation.getInitialParticleYStdDev() << ";"
              << simulation.getMeanInitialParticleTheta() << ";"
              << simulation.getInitialParticleThetaStdDev() << "\n";
  } else {
    std::cout << "\n------ Stats ------\n";
    std::cout << simulation.getStats() << "\n";
  }
}