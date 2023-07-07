#include <SFML/Graphics.hpp>
#include <iostream>

#include "graphics/font.hpp"
#include "graphics/window.hpp"
#include "math/angles.hpp"
#include "simulation.hpp"
#include "util/arguments.hpp"

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

    loadFonts();  // throws runtime_error if unable to find a font file

    Simulation simulation(config.r1, config.r2, config.l, config.meanInitialY,
                          config.stddevInitialY, config.meanInitialTheta,
                          config.stddevInitialTheta);

    if (config.graphics) {
      GraphicsWindow window(simulation);
      window.show();
    } else {
      simulation.addNewIterationListener([](Particle const& particle) {
        std::cout << "\tStart\t\tpos: " << particle.getPosition()
                  << ", theta: " << degrees(particle.getTheta()) << "°\n";
      });
      simulation.addCollisionListener([](Particle const& particle) {
        std::cout << "\tCollision\tpos: " << particle.getPosition()
                  << ", theta: " << degrees(particle.getTheta()) << "°\n";
      });
      simulation.addIterationEndedListener([](Particle const& particle) {
        std::cout << "\tEnd\tpos: " << particle.getPosition()
                  << ", theta: " << degrees(particle.getTheta()) << "°\n";
      });
      for (int i = 0; i < config.iterations; i++) {
        std::cout << "Iteration #" << (i + 1) << "\n";
        simulation.newIteration();
        simulation.immediate();
        std::cout << simulation.getStats() << "\n";
      }
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