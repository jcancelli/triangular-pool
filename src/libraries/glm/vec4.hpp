/// @ref core
/// @file glm/vec4.hpp

#pragma once
#include <ostream>

#include "./ext/vector_bool4.hpp"
#include "./ext/vector_bool4_precision.hpp"
#include "./ext/vector_double4.hpp"
#include "./ext/vector_double4_precision.hpp"
#include "./ext/vector_float4.hpp"
#include "./ext/vector_float4_precision.hpp"
#include "./ext/vector_int4.hpp"
#include "./ext/vector_int4_sized.hpp"
#include "./ext/vector_uint4.hpp"
#include "./ext/vector_uint4_sized.hpp"

namespace glm {

template <class T, qualifier Q>
inline std::ostream& operator<<(std::ostream& os, vec<4, T, Q> const& vector) {
  return os << "{ x: " << vector.x << ", y: " << vector.y << ", z: " << vector.z
            << ", w: " << vector.w << " }";
}

}  // namespace glm
