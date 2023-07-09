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
  m_CoordsScalingChangedListeners.notify(factor);
}

double Graphics::getCoordsScaling() const {
  return m_CoordsScaling;
}

unsigned Graphics::addCoordsScalingChangeListener(util::Listeners<double>::Listener listener) {
  return m_CoordsScalingChangedListeners.add(listener);
}

void Graphics::removeCoordsScalingChangeListener(unsigned listenerID) {
  m_CoordsScalingChangedListeners.remove(listenerID);
}

}  // namespace graphics

}  // namespace pool