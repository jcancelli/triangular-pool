#ifndef GRAPHICS_WINDOW_HPP
#define GRAPHICS_WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "../simulation.hpp"
#include "simulation.hpp"

class GraphicsWindow {
 private:
  sf::RenderWindow m_Window;
  SimulationGraphics m_SimulationGraphics;

 public:
  GraphicsWindow(unsigned width, unsigned height, Simulation const& simulation);

  void show();

 private:
  void processEvents();
};

#endif