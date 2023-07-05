/// @ref core
/// @file glm/vec3.hpp

#pragma once
#include <ostream>

#include "./ext/vector_bool3.hpp"
#include "./ext/vector_bool3_precision.hpp"
#include "./ext/vector_double3.hpp"
#include "./ext/vector_double3_precision.hpp"
#include "./ext/vector_float3.hpp"
#include "./ext/vector_float3_precision.hpp"
#include "./ext/vector_int3.hpp"
#include "./ext/vector_int3_sized.hpp"
#include "./ext/vector_uint3.hpp"
#include "./ext/vector_uint3_sized.hpp"

namespace glm {

template <class T, qualifier Q>
inline std::ostream& operator<<(std::ostream& os, vec<3, T, Q> const& vector) {
  return os << "{ x: " << vector.x << ", y: " << vector.y << ", z: " << vector.z << " }";
}

}  // namespace glm
