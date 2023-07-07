#ifndef GRAPHICS_SIMULATION_HPP
#define GRAPHICS_SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "../simulation.hpp"
#include "graphics.hpp"
#include "particle.hpp"
#include "wall.hpp"

class SimulationGraphics : public Graphics {
 private:
  Simulation const& m_Simulation;
  WallGraphics m_UpperWallGraphics, m_LowerWallGraphics;
  ParticleGraphics m_ParticleGraphics;
  double m_CoordinatesScaling;

 public:
  SimulationGraphics(Simulation const& simulation);

  void update(double deltaTimeMs);
  void setCoordinatesScaling(double factor);
  double getCoordinatesScaling() const;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif