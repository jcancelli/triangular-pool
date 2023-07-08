#ifndef MATH_STATISTICS_HPP
#define MATH_STATISTICS_HPP

#include <optional>
#include <type_traits>
#include <vector>

namespace pool {

namespace math {

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double mean(std::vector<T> const& values);

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double variance(std::vector<T> const& values, std::optional<double> meanOpt = {});

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double stdDev(std::vector<T> const& values, std::optional<double> meanOpt = {});

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double median(std::vector<T> values);

// https://exploringfinance.com/skewness-calculator/
template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double skewness(std::vector<T> const& values, std::optional<double> meanOpt = {},
                std::optional<double> stdDevOpt = {});

// https://exploringfinance.com/kurtosis-calculator/
template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double kurtosis(std::vector<T> const& values, std::optional<double> meanOpt = {},
                std::optional<double> stdDevOpt = {});

}  // namespace math

}  // namespace pool

#include "statistics.inl"

#endif