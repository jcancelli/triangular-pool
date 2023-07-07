#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "math/statistics.hpp"

#include <doctest/doctest.h>

TEST_CASE("Testing mean") {
  std::vector<double> values;

  SUBCASE("0 values") {
    CHECK_THROWS(mean(values));
  }

  SUBCASE("1 value") {
    values.push_back(5);
    CHECK_EQ(mean(values), 5);
  }

  SUBCASE("n values") {
    values.push_back(6);
    values.push_back(-11);
    values.push_back(3);
    values.push_back(-4);
    CHECK_EQ(mean(values), -1.5);
  }
}

TEST_CASE("Testing variance") {
  std::vector<double> values;

  SUBCASE("0 values") {
    CHECK_THROWS(variance(values));
  }

  SUBCASE("1 value") {
    values.push_back(5);
    CHECK_THROWS(variance(values));
  }

  SUBCASE("n values") {
    values.push_back(6.0);
    values.push_back(-11.0);
    values.push_back(3.0);
    values.push_back(-4.0);
    CHECK_EQ(variance(values), doctest::Approx(57.666667));
  }
}

TEST_CASE("Testing stdDev") {
  std::vector<double> values;

  SUBCASE("0 values") {
    CHECK_THROWS(stdDev(values));
  }

  SUBCASE("1 value") {
    values.push_back(5);
    CHECK_THROWS(stdDev(values));
  }

  SUBCASE("n values") {
    values.push_back(6.0);
    values.push_back(-11.0);
    values.push_back(3.0);
    values.push_back(-4.0);
    CHECK_EQ(stdDev(values), doctest::Approx(7.5938571666));
  }
}