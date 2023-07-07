#ifndef MATH_STATISTICS_HPP
#define MATH_STATISTICS_HPP

#include <optional>
#include <type_traits>
#include <vector>

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double mean(std::vector<T> const& values);

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double variance(std::vector<T> const& values, std::optional<double> meanOpt = {});

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double stdDev(std::vector<T> const& values, std::optional<double> meanOpt = {});

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double median(std::vector<T> values);

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double skewness(std::vector<T> const& values, std::optional<double> meanOpt = {},
                std::optional<double> stdDevOpt = {});

#include "statistics.inl"

#endif