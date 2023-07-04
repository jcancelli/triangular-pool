#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "linear_equation.hpp"

#include <doctest/doctest.h>

TEST_CASE("Testing LinearEquation") {
  LinearEquation f;

  SUBCASE("Negative gradient") {
    f.gradient = -2;

    SUBCASE("Negative offset") {
      f.offset = -2;
      CHECK(f(-2) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(-4).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(-6).epsilon(.0000000001));
    }
    SUBCASE("0 offset") {
      f.offset = 0;
      CHECK(f(-2) == doctest::Approx(4).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(-4).epsilon(.0000000001));
    }
    SUBCASE("Positive offset") {
      f.offset = 2;
      CHECK(f(-2) == doctest::Approx(6).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(4).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(-2).epsilon(.0000000001));
    }
  }

  SUBCASE("0 gradient") {
    f.gradient = 0;

    SUBCASE("Negative offset") {
      f.offset = -2;
      CHECK(f(-2) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(-2).epsilon(.0000000001));
    }
    SUBCASE("0 offset") {
      f.offset = 0;
      CHECK(f(-2) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(0).epsilon(.0000000001));
    }
    SUBCASE("Positive offset") {
      f.offset = 2;
      CHECK(f(-2) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(2).epsilon(.0000000001));
    }
  }

  SUBCASE("Positive gradient") {
    f.gradient = 2;

    SUBCASE("Negative offset") {
      f.offset = -2;
      CHECK(f(-2) == doctest::Approx(-6).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(-4).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(2).epsilon(.0000000001));
    }
    SUBCASE("0 offset") {
      f.offset = 0;
      CHECK(f(-2) == doctest::Approx(-4).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(4).epsilon(.0000000001));
    }
    SUBCASE("Positive offset") {
      f.offset = 2;
      CHECK(f(-2) == doctest::Approx(-2).epsilon(.0000000001));
      CHECK(f(-1) == doctest::Approx(0).epsilon(.0000000001));
      CHECK(f(0) == doctest::Approx(2).epsilon(.0000000001));
      CHECK(f(1) == doctest::Approx(4).epsilon(.0000000001));
      CHECK(f(2) == doctest::Approx(6).epsilon(.0000000001));
    }
  }
}