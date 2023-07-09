#include <SFML/Graphics.hpp>
#include <iostream>

#include "graphics/font.hpp"
#include "graphics/window.hpp"
#include "math/angles.hpp"
#include "simulation.hpp"
#include "util/arguments.hpp"

/* TODO: Change how the simulation handles particles coming out of the back. The simulation should
         consider iterations where the particles comes out of the back as "failed" and should track
         failed iterations statistics.

        TODO: Use addOnCoordsScalingChangeListener on all graphics objects that could use it
*/

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
      std::cout << "R1;R2;L;Number of iterations;Mean final y;Mean final theta;Average number of "
                   "collisions per iteration;Standard deviation final y;Standard deviation final "
                   "theta;Skewness final y;Skewness final theta;Kurtosis final y;Kurtosis final "
                   "theta;Mean initial y;Standard deviation initial y;Mean initial theta;Standard "
                   "deviation initial theta\n";
    }
    std::cout << simulation.getR1() << ";" << simulation.getR2() << ";" << simulation.getL() << ";"
              << simulation.getStats().toCSVString() << ";" << simulation.getMeanInitialParticleY()
              << ";" << simulation.getInitialParticleYStdDev() << ";"
              << simulation.getMeanInitialParticleTheta() << ";"
              << simulation.getInitialParticleThetaStdDev() << "\n";
  } else {
    std::cout << simulation.getStats().toString(config.verboseOutput) << "\n";
  }
}