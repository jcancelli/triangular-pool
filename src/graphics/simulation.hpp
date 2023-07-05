#ifndef GRAPHICS_SIMULATION_HPP
#define GRAPHICS_SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <string>

class SimulationGraphics {
 private:
  sf::RenderWindow m_Window;

 public:
  SimulationGraphics(unsigned width, unsigned height, std::string const& title,
                     unsigned antialiasing);

  void show();

 private:
  void processEvents();
};

#endif