#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <glm/vec2.hpp>
#include <optional>

#include "linear_equation.hpp"
#include "segment.hpp"

std::optional<glm::vec2> lineLineIntersection(LinearEquation const& a, LinearEquation const& b);
std::optional<glm::vec2> lineSegmentIntersection(LinearEquation const& line,
                                                 Segment const& segment);
std::optional<glm::vec2> segmentSegmentIntersection(Segment const& a, Segment const& b);

#endif