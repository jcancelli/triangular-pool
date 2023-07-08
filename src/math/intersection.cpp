#include "intersection.hpp"

#include "segment.hpp"

namespace pool {

namespace math {

std::optional<glm::vec2> intersection(LinearEquation const& a, LinearEquation const& b) {
  if (a.gradient == b.gradient || !a.isValid() || !b.isValid()) {
    return {};
  }
  const double x = (b.offset - a.offset) / (a.gradient - b.gradient);
  const double y = (b.gradient * a.offset - a.gradient * b.offset) / (b.gradient - a.gradient);
  return glm::vec2(x, y);
}

std::optional<glm::vec2> intersection(LinearEquation const& line, Segment const& segment) {
  if (!line.isValid()) {
    return {};
  }
  auto segmentEquation = segment.getLineEquation();
  if (!segmentEquation.isValid()) {  // segment is vertical
    const glm::vec2 possibleIntersection(segment.getA().x, line(segment.getA().x));
    return segment.couldContain(possibleIntersection) ? possibleIntersection
                                                      : std::optional<glm::vec2>();
  }
  const auto intersectionOpt = intersection(line, segmentEquation);
  if (!intersectionOpt.has_value()) {
    return {};
  }
  glm::vec2 const& intersection = intersectionOpt.value();
  if (!segment.couldContain(intersection)) {
    return {};
  }
  return intersection;
}

std::optional<glm::vec2> intersection(Segment const& segment, LinearEquation const& line) {
  return intersection(line, segment);
}

std::optional<glm::vec2> intersection(LinearEquation const& line, Ray const& ray) {
  return intersection(ray, line);
}

std::optional<glm::vec2> intersection(Ray const& ray, LinearEquation const& line) {
  if (!line.isValid()) {
    return {};
  }
  auto rayEquation = ray.getLineEquation();
  if (!rayEquation.isValid()) {  // ray is vertical
    const glm::vec2 possibleIntersection(ray.getOrigin().x, line(ray.getOrigin().x));
    return ray.couldContain(possibleIntersection) ? possibleIntersection
                                                  : std::optional<glm::vec2>();
  }
  const auto intersectionOpt = intersection(rayEquation, line);
  if (!intersectionOpt.has_value()) {
    return {};
  }
  glm::vec2 const& intersection = intersectionOpt.value();
  if (!ray.couldContain(intersection)) {
    return {};
  }
  return intersection;
}

std::optional<glm::vec2> intersection(Ray const& ray, Segment const& segment) {
  LinearEquation rayEquation = ray.getLineEquation();
  LinearEquation segmentEquation = segment.getLineEquation();
  if (!rayEquation.isValid()) {        // ray is vertical
    if (!segmentEquation.isValid()) {  // segment is vertical
      return {};
    }
    const glm::vec2 possibleIntersection(ray.getOrigin().x, segmentEquation(ray.getOrigin().x));
    return ray.couldContain(possibleIntersection) && segment.couldContain(possibleIntersection)
               ? possibleIntersection
               : std::optional<glm::vec2>();
  }
  if (!segmentEquation.isValid()) {  // segment is vertical (but ray not vertical)
    const glm::vec2 possibleIntersection(segment.getA().x, rayEquation(segment.getA().x));
    return ray.couldContain(possibleIntersection) && segment.couldContain(possibleIntersection)
               ? possibleIntersection
               : std::optional<glm::vec2>();
  }
  const auto intersectionOpt = intersection(rayEquation, segmentEquation);
  if (!intersectionOpt.has_value()) {
    return {};
  }
  glm::vec2 const& intersection = intersectionOpt.value();
  if (!ray.couldContain(intersection) || !segment.couldContain(intersection)) {
    return {};
  }
  return intersection;
}

std::optional<glm::vec2> intersection(Segment const& segment, Ray const& ray) {
  return intersection(ray, segment);
}

std::optional<glm::vec2> intersection(Ray const& a, Ray const& b) {
  // TODO: Implement intersection vertical ray / vertical ray
  LinearEquation rayAEquation = a.getLineEquation();
  LinearEquation rayBEquation = b.getLineEquation();
  const std::optional<glm::vec2> intersectionOpt = intersection(rayAEquation, rayBEquation);
  if (!intersectionOpt.has_value()) {
    return {};
  }
  glm::vec2 const& intersection = intersectionOpt.value();
  if (!a.couldContain(intersection)) {
    return {};
  }
  return intersection;
}

std::optional<glm::vec2> intersection(Segment const& a, Segment const& b) {
  // TODO: Implement intersection vertical segment / vertical segment
  LinearEquation segmentAEquation = a.getLineEquation();
  LinearEquation segmentBEquation = b.getLineEquation();
  const std::optional<glm::vec2> intersectionOpt = intersection(segmentAEquation, segmentBEquation);
  if (!intersectionOpt.has_value()) {
    return {};
  }
  glm::vec2 const& intersection = intersectionOpt.value();
  if (!a.couldContain(intersection)) {
    return {};
  }
  return intersection;
}

}  // namespace math

}  // namespace pool