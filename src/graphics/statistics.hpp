#ifndef GRAPHICS_STATISTICS_HPP
#define GRAPHICS_STATISTICS_HPP

#include <SFML/Graphics/Text.hpp>

#include "../simulation.hpp"
#include "graphics.hpp"

class StatisticsGraphics : public Graphics {
 private:
  Simulation const& m_Simulation;
  sf::Text m_Text;

 public:
  StatisticsGraphics(Simulation& simulation);

  void update(sf::Time const& elapsed) override;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  void updateText();
};

#endif