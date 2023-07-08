#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <glm/vec2.hpp>
#include <optional>

#include "linear_equation.hpp"
#include "ray.hpp"
#include "segment.hpp"

namespace pool {

namespace math {

std::optional<glm::vec2> intersection(LinearEquation const& a, LinearEquation const& b);
std::optional<glm::vec2> intersection(Ray const& a, Ray const& b);
std::optional<glm::vec2> intersection(Segment const& a, Segment const& b);
std::optional<glm::vec2> intersection(LinearEquation const& line, Ray const& ray);
std::optional<glm::vec2> intersection(Ray const& ray, LinearEquation const& line);
std::optional<glm::vec2> intersection(LinearEquation const& line, Segment const& segment);
std::optional<glm::vec2> intersection(Segment const& segment, LinearEquation const& line);
std::optional<glm::vec2> intersection(Ray const& ray, Segment const& segment);
std::optional<glm::vec2> intersection(Segment const& segment, Ray const& ray);

}  // namespace math

}  // namespace pool

#endif