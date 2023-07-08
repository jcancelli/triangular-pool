#include "graphics.hpp"

void Graphics::update(sf::Time const& delta) {
}

void Graphics::setCoordsScaling(double factor) {
  m_CoordsScaling = factor;
}

double Graphics::getCoordsScaling() const {
  return m_CoordsScaling;
}
