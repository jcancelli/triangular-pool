#include "angles.hpp"

namespace pool {

namespace math {

static const double RAD_TO_DEG = 57.295779513082320876798154814105;
static const double DEG_TO_RAD = 0.01745329251994329576923690768489;

double radians(double deg) {
  return deg * DEG_TO_RAD;
}

double degrees(double rad) {
  return rad * RAD_TO_DEG;
}

}  // namespace math

}  // namespace pool