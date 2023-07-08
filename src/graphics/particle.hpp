#ifndef GRAPHICS_PARTICLE_HPP
#define GRAPHICS_PARTICLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "../particle.hpp"
#include "graphics.hpp"
#include "point.hpp"

namespace pool {

namespace graphics {

class ParticleGraphics : public Graphics {
 private:
  Particle const& m_Particle;
  PointGraphics m_Point;
  sf::RectangleShape m_VelocityLine;

 public:
  ParticleGraphics(Particle const& particle);

  void update(sf::Time const& delta) override;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  void updatePosition();
  void updateText();
  void updateVelocityLine();
};

}  // namespace graphics

}  // namespace pool

#endif