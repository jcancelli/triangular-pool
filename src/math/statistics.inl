#ifndef MATH_STATISTICS_INL
#define MATH_STATISTICS_INL

#include <algorithm>
#include <cmath>
#include <iostream>
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
double variance(std::vector<T> const& values, std::optional<double> meanOpt) {
  if (values.size() < 2) {
    throw std::invalid_argument("Error: Cannot calculate variance of n < 2 samples");
  }
  if (!meanOpt.has_value()) {
    meanOpt = mean(values);
  }
  auto computeNum = [meanOpt](auto sum, auto val) {
    return sum + std::pow(val - meanOpt.value(), 2);
  };
  return std::accumulate(values.cbegin(), values.cend(), 0.0, computeNum) /
         static_cast<double>(values.size() - 1);
}

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double stdDev(std::vector<T> const& values, std::optional<double> meanOpt) {
  if (values.size() < 2) {
    throw std::invalid_argument("Error: Cannot calculate standerd deviation of n < 2 samples");
  }
  return std::sqrt(variance(values, meanOpt));
}

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double median(std::vector<T> values) {
  if (values.size() == 0) {
    throw std::invalid_argument("Error: Cannot find median of 0 elements");
  }
  if (values.size() % 2 == 0) {
    std::sort(values.begin(), values.end());
    T low = values[values.size() / 2.0 - 1];
    T high = values[values.size() / 2.0];
    return (low + high) / 2.0;
  }
  std::size_t n = values.size() / 2;
  std::nth_element(values.begin(), values.begin() + n, values.end());
  return values[n];
}

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double skewness(std::vector<T> const& values, std::optional<double> meanOpt,
                std::optional<double> stdDevOpt) {
  if (values.size() < 2) {
    throw std::invalid_argument("Error: Cannot calculate skewness of n < 2 elements");
  }
  if (!meanOpt.has_value()) {
    meanOpt = mean(values);
  }
  if (!stdDevOpt.has_value()) {
    stdDevOpt = stdDev(values, meanOpt);
  }
  auto computeNum = [meanOpt](auto sum, auto val) {
    return sum + std::pow(val - meanOpt.value(), 3);
  };
  double numerator = std::accumulate(values.cbegin(), values.cend(), 0.0, computeNum);
  double denominator = (double(values.size()) - 1) * std::pow(stdDevOpt.value(), 3);
  return numerator / denominator;
}

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
double kurtosis(std::vector<T> const& values, std::optional<double> meanOpt,
                std::optional<double> stdDevOpt) {
  const int n = values.size();
  if (n < 2) {
    throw std::invalid_argument("Error: Cannot calculate kurtosis of n < 2 elements");
  }
  if (!meanOpt.has_value()) {
    meanOpt = mean(values);
  }
  if (!stdDevOpt.has_value()) {
    stdDevOpt = stdDev(values, meanOpt);
  }
  auto computeNum = [meanOpt](auto sum, auto val) {
    return sum + std::pow(val - meanOpt.value(), 4);
  };
  double num = std::accumulate(values.cbegin(), values.cend(), 0.0, computeNum);
  double denom = (n - 1.0) * std::pow(stdDevOpt.value(), 4);
  return num / denom;
}

#endif