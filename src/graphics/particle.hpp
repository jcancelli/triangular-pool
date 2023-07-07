#ifndef GRAPHICS_PARTICLE_HPP
#define GRAPHICS_PARTICLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../particle.hpp"
#include "graphics.hpp"
#include "point.hpp"

class ParticleGraphics : public Graphics {
 private:
  Particle const& m_Particle;
  PointGraphics m_Point;
  sf::RectangleShape m_VelocityLine;
  double m_CoordinatesScalingFactor;

 public:
  ParticleGraphics(Particle const& particle);

  void update(double deltaTimeMs);
  void setCoordinatesScaling(double factor);
  double getCoordinatesScaling() const;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  void updatePosition();
  void updateText();
  void updateVelocityLine();
};

#endif