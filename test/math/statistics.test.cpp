#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "math/statistics.hpp"

#include <doctest/doctest.h>

TEST_CASE("Testing mean") {
  std::vector<double> values;

  SUBCASE("Testing n: 0") {
    CHECK_THROWS(mean(values));
  }

  SUBCASE("Testing n: 1") {
    values.push_back(5);
    CHECK_EQ(mean(values), 5);
  }

  SUBCASE("Testing n: n") {
    values.push_back(6);
    values.push_back(-11);
    values.push_back(3);
    values.push_back(-4);
    CHECK_EQ(mean(values), -1.5);
  }
}

TEST_CASE("Testing variance") {
  std::vector<double> values;

  SUBCASE("Testing n: 0") {
    CHECK_THROWS(variance(values));
  }

  SUBCASE("Testing n: 1") {
    values.push_back(5);
    CHECK_THROWS(variance(values));
  }

  SUBCASE("Testing n: n") {
    values.push_back(6.0);
    values.push_back(-11.0);
    values.push_back(3.0);
    values.push_back(-4.0);
    CHECK_EQ(variance(values), doctest::Approx(57.666667));
  }
}

TEST_CASE("Testing stdDev") {
  std::vector<double> values;

  SUBCASE("Testing n: 0") {
    CHECK_THROWS(stdDev(values));
  }

  SUBCASE("Testing n: 1") {
    values.push_back(5);
    CHECK_THROWS(stdDev(values));
  }

  SUBCASE("Testing n: n") {
    values.push_back(6.0);
    values.push_back(-11.0);
    values.push_back(3.0);
    values.push_back(-4.0);
    CHECK_EQ(stdDev(values), doctest::Approx(7.5938571666));
  }
}

TEST_CASE("Testing median") {
  std::vector<double> values;

  SUBCASE("Testing n: 0") {
    CHECK_THROWS(median(values));
  }

  SUBCASE("Testing n: 1") {
    values.push_back(5);
    CHECK_EQ(median(values), 5);
  }

  SUBCASE("Testing n: n") {
    values.push_back(6.0);
    values.push_back(-11.0);
    values.push_back(3.0);
    values.push_back(-4.0);
    CHECK_EQ(median(values), -0.5);
  }
}

TEST_CASE("Testing skewness") {
  std::vector<double> values;

  SUBCASE("Testing n: 0") {
    CHECK_THROWS(skewness(values));
  }

  SUBCASE("Testing n: 1") {
    values.push_back(5);
    CHECK_THROWS(skewness(values));
  }

  SUBCASE("Testing n: n") {
    values.push_back(6.0);
    values.push_back(-11.0);
    values.push_back(3.0);
    values.push_back(-4.0);
    values.push_back(-0.4);
    CHECK_EQ(skewness(values), doctest::Approx(-0.41275));
  }
}