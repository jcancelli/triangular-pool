#include "arguments.hpp"

#include <argumentum/argparse-h.h>

namespace pool {

namespace util {

ParseStatus parseArguments(int argc, char* argv[], Config& config) {
  ParseStatus status = ParseStatus::Success;
  auto parser = argumentum::argument_parser{};
  auto params = parser.params();

  parser.config().program(argv[0]).description("Simulation of a triangular pool");

  params.add_parameter(config.r1, "--r1")
      .default_value(config.r1)
      .nargs(1)
      .help("Value of y of the leftmost extreme of the upper wall (-r1 for the lower wall).");
  params.add_parameter(config.r2, "--r2")
      .default_value(config.r2)
      .nargs(1)
      .help("Value of y of the rightmost extreme of the upper wall (-r2 for the lower wall).");
  params.add_parameter(config.l, "--l")
      .default_value(config.l)
      .nargs(1)
      .help("Value of x of the rightmost extreme of both walls.");
  params.add_parameter(config.iterations, "--n")
      .default_value(config.iterations)
      .nargs(1)
      .help("Number of iterations of the simulation.");
  params.add_parameter(config.meanInitialY, "--mean-y")
      .default_value(config.meanInitialY)
      .nargs(1)
      .help("Mean value of the initial y coordinate of the particle (normal distribution).");
  params.add_parameter(config.stddevInitialY, "--std-dev-y")
      .default_value(config.stddevInitialY)
      .nargs(1)
      .help("Standard deviation of the initial particle y coordinate.");
  params.add_parameter(config.meanInitialTheta, "--mean-theta")
      .default_value(config.meanInitialTheta)
      .nargs(1)
      .help(
          "Mean value of the initial angle of direction of the particle in degrees (normal "
          "distribution).");
  params.add_parameter(config.stddevInitialTheta, "--std-dev-theta")
      .default_value(config.stddevInitialTheta)
      .nargs(1)
      .help("Standard deviation of the initial particle direction angle value.");
  params.add_parameter(config.simulationSpeed, "--speed")
      .default_value(config.simulationSpeed)
      .nargs(1)
      .help(
          "Speed of the simulation. If the flag --graphics is not present this value will be "
          "ignored.");
  params.add_parameter(config.verboseOutput, "--verbose")
      .default_value(config.verboseOutput)
      .flagValue("1")
      .help("Value of y of the leftmost extreme of the upper wall (-r1 for the lower wall).");
  params.add_parameter(config.graphics, "--graphics")
      .default_value(config.graphics)
      .flagValue("1")
      .help(
          "Enables graphical visualization of the simulation. In graphical mode the "
          "simulation keeps iterating until the program is stopped (the parameter n is ignored).");

  try {
    argumentum::ParseResult parseResults = parser.parse_args(argc, argv);

    if (!parseResults) {
      if (parseResults.errors.size()) {
        for (auto const& error : parseResults.errors) {
          error.describeError(std::cout);
          status = ParseStatus::Error;
        }
      }
    }

    if (parseResults.help_was_shown()) {
      status = ParseStatus::HelpShown;
      return status;
    }

    validateConfig(config);

  } catch (std::invalid_argument const& e) {
    std::cout << e.what() << "\n";
    status = ParseStatus::Error;
  } catch (std::exception const& e) {
    std::cout << "Unexpected error\n";
    std::cout << e.what() << "\n";
    status = ParseStatus::Error;
  } catch (...) {
    std::cout << "Unknown error\n";
    status = ParseStatus::Error;
  }

  return status;
}

}  // namespace util

}  // namespace pool