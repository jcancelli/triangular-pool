#ifndef GRAPHICS_WINDOW_HPP
#define GRAPHICS_WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "../simulation.hpp"
#include "simulation.hpp"

class GraphicsWindow {
 private:
  sf::RenderWindow m_Window;
  sf::Clock m_Clock;
  SimulationGraphics m_SimulationGraphics;
  Simulation& m_Simulation;

 public:
  GraphicsWindow(Simulation& simulation);

  void show();

 private:
  void processWindowEvents();
};

#endif