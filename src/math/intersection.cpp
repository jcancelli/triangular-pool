#include "intersection.hpp"

#include "segment.hpp"

std::optional<glm::vec2> intersection(LinearEquation const& a, LinearEquation const& b) {
  if (a.gradient == b.gradient) {
    return {};
  }
  const double x = (b.offset - a.offset) / (a.gradient - b.gradient);
  const double y = (b.gradient * a.offset - a.gradient * b.offset) / (b.gradient - a.gradient);
  return glm::vec2(x, y);
}

std::optional<glm::vec2> intersection(LinearEquation const& line, Segment const& segment) {
  LinearEquation segmentEquation = segment.getLineEquation();
  const std::optional<glm::vec2> intersectionOpt = intersection(line, segmentEquation);
  if (!intersectionOpt.has_value()) {
    return {};
  }
  glm::vec2 const& intersection = intersectionOpt.value();
  if (!segment.couldContain(intersection)) {
    return {};
  }
  return intersection;
}

std::optional<glm::vec2> intersection(Ray const& ray, LinearEquation const& line) {
  LinearEquation rayEquation = ray.getLineEquation();
  const std::optional<glm::vec2> intersectionOpt = intersection(rayEquation, line);
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
  const std::optional<glm::vec2> intersectionOpt = intersection(rayEquation, segmentEquation);
  if (!intersectionOpt.has_value()) {
    return {};
  }
  glm::vec2 const& intersection = intersectionOpt.value();
  if (!ray.couldContain(intersection)) {
    return {};
  }
  return intersection;
}

std::optional<glm::vec2> intersection(Ray const& a, Ray const& b) {
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