#ifndef MATH_STATISTICS_INL
#define MATH_STATISTICS_INL

#include <cmath>
#include <numeric>
#include <stdexcept>

#include "statistics.hpp"

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double mean(std::vector<T> const& values) {
  if (values.size() < 1) {
    throw std::invalid_argument("Error: Cannot calculate average of n < 1 samples");
  }
  return std::accumulate(values.cbegin(), values.cend(), 0.0) / static_cast<double>(values.size());
}

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double variance(std::vector<T> const& values, std::optional<double> cachedMean) {
  if (values.size() < 2) {
    throw std::invalid_argument("Error: Cannot calculate variance of n < 2 samples");
  }
  if (!cachedMean.has_value()) {
    cachedMean = mean(values);
  }
  auto computeNum = [cachedMean](auto sum, auto val) {
    return sum + std::pow(val - cachedMean.value(), 2);
  };
  return std::accumulate(values.cbegin(), values.cend(), 0.0, computeNum) /
         static_cast<double>(values.size() - 1);
}

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double stdDev(std::vector<T> const& values, std::optional<double> cachedMean) {
  if (values.size() < 2) {
    throw std::invalid_argument("Error: Cannot calculate standerd deviation of n < 2 samples");
  }
  return std::sqrt(variance(values, cachedMean));
}

#endif