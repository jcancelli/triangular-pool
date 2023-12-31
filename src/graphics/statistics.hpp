#ifndef GRAPHICS_STATISTICS_HPP
#define GRAPHICS_STATISTICS_HPP

#include <SFML/Graphics/Text.hpp>

#include "../simulation.hpp"
#include "graphics.hpp"

namespace pool {

namespace graphics {

class StatisticsGraphics : public Graphics {
 private:
  Simulation const& m_Simulation;
  sf::Text m_Labels, m_Values;

 public:
  StatisticsGraphics(Simulation& simulation);

  void update(sf::Time const& elapsed) override;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  void updateText();
};

}  // namespace graphics

}  // namespace pool

#endif