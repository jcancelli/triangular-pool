#include "graphics.hpp"

#include "../util/unused.hpp"

namespace pool {

namespace graphics {

Graphics::Graphics() : m_CoordsScaling{1.0} {
}

void Graphics::update(sf::Time const& delta) {
  UNUSED(delta);
}

void Graphics::setCoordsScaling(double factor) {
  m_CoordsScaling = factor;
}

double Graphics::getCoordsScaling() const {
  return m_CoordsScaling;
}

}  // namespace graphics

}  // namespace pool