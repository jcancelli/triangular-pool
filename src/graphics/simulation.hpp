#ifndef GRAPHICS_SIMULATION_HPP
#define GRAPHICS_SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "../simulation.hpp"

class SimulationGraphics {
 private:
  sf::RenderWindow m_Window;
  Simulation const& m_Simulation;

 public:
  SimulationGraphics(unsigned width, unsigned height, Simulation const& simulation);

  void show();

 private:
  void processEvents();
};

#endif