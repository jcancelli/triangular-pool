#ifndef GRAPHICS_WALL_HPP
#define GRAPHICS_WALL_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../wall.hpp"
#include "graphics.hpp"
#include "point.hpp"

class WallGraphics : public Graphics {
 private:
  Wall const& m_Wall;
  sf::RectangleShape m_Line;
  PointGraphics m_PointA, m_PointB;
  double m_CoordinatesScaling;

 public:
  WallGraphics(Wall const& wall);

  void update(double deltaTimeMs);
  void setCoordinatesScaling(double factor);
  double getCoordinatesScaling() const;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  void updatePointsText();
};

#endif