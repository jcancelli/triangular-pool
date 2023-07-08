#ifndef GRAPHICS_SIMULATION_HPP
#define GRAPHICS_SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../simulation.hpp"
#include "graphics.hpp"
#include "particle.hpp"
#include "wall.hpp"

class SimulationGraphics : public Graphics {
 private:
  Simulation& m_Simulation;
  WallGraphics m_UpperWallGraphics, m_LowerWallGraphics;
  ParticleGraphics m_ParticleGraphics;
  std::vector<PointGraphics> m_CollisionPointsGraphics;
  std::vector<PointGraphics> m_FinalPositionsPointsGraphics;

 public:
  SimulationGraphics(Simulation& simulation);

  void update(sf::Time const& delta) override;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif