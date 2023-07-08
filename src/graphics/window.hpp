#ifndef GRAPHICS_WINDOW_HPP
#define GRAPHICS_WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "../simulation.hpp"
#include "simulation.hpp"
#include "statistics.hpp"

namespace pool {

namespace graphics {

class GraphicsWindow {
 private:
  sf::RenderWindow m_Window;
  sf::Clock m_Clock;
  SimulationGraphics m_SimulationGraphics;
  StatisticsGraphics m_StatisticsGraphics;
  Simulation& m_Simulation;

 public:
  GraphicsWindow(Simulation& simulation);

  void show();

 private:
  void processWindowEvents();
};

}  // namespace graphics

}  // namespace pool

#endif