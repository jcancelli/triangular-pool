#ifndef GRAPHICS_GRAPHICS_HPP
#define GRAPHICS_GRAPHICS_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>

class Graphics : public sf::Drawable, public sf::Transformable {
 private:
  double m_CoordsScaling;

 public:
  virtual void update(sf::Time const& delta);
  void setCoordsScaling(double factor);
  double getCoordsScaling() const;
};

#endif