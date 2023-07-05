/// @ref core
/// @file glm/vec2.hpp

#pragma once
#include <ostream>

#include "./ext/vector_bool2.hpp"
#include "./ext/vector_bool2_precision.hpp"
#include "./ext/vector_double2.hpp"
#include "./ext/vector_double2_precision.hpp"
#include "./ext/vector_float2.hpp"
#include "./ext/vector_float2_precision.hpp"
#include "./ext/vector_int2.hpp"
#include "./ext/vector_int2_sized.hpp"
#include "./ext/vector_uint2.hpp"
#include "./ext/vector_uint2_sized.hpp"

namespace glm {

template <class T, qualifier Q>
inline std::ostream& operator<<(std::ostream& os, vec<2, T, Q> const& vector) {
  return os << "{ x: " << vector.x << ", y: " << vector.y << " }";
}

};  // namespace glm