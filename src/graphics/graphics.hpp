#ifndef GRAPHICS_GRAPHICS_HPP
#define GRAPHICS_GRAPHICS_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>

#include "../util/listeners.hpp"

namespace pool {

namespace graphics {

class Graphics : public sf::Drawable, public sf::Transformable {
 private:
  double m_CoordsScaling;
  util::Listeners<double> m_CoordsScalingChangedListeners;

 public:
  Graphics();

  virtual void update(sf::Time const& delta);
  void setCoordsScaling(double factor);
  double getCoordsScaling() const;
  unsigned addCoordsScalingChangeListener(util::Listeners<double>::Listener listener);
  void removeCoordsScalingChangeListener(unsigned listenerID);
};

}  // namespace graphics

}  // namespace pool

#endif