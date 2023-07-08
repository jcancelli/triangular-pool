#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "math/segment.hpp"

#include <doctest/doctest.h>

#include <cmath>

using namespace pool::math;

TEST_CASE("Testing Segment") {
  SUBCASE("Testing constructors") {
    SUBCASE("x1 y1 x2 y2") {
      Segment s(1, 2, 3, 4);
      CHECK_EQ(s.getA(), glm::vec2(1, 2));
      CHECK_EQ(s.getB(), glm::vec2(3, 4));
    }
    SUBCASE("a b") {
      const glm::vec2 a(1, 2);
      const glm::vec2 b(3, 4);
      Segment s(a, b);
      CHECK_EQ(s.getA(), a);
      CHECK_EQ(s.getB(), b);
    }
    SUBCASE("equation x1 x2") {
      LinearEquation equation{-2, 0};
      Segment s(equation, 1, 5);
      CHECK_EQ(s.getA(), glm::vec2(1, -2));
      CHECK_EQ(s.getB(), glm::vec2(5, -10));
    }
    SUBCASE("copy contructor") {
      Segment s1(1, 2, 3, 4);
      Segment s2(s1);
      CHECK_EQ(s2.getA(), s1.getA());
      CHECK_EQ(s2.getB(), s1.getB());
    }
  }
  SUBCASE("Testing setters") {
    Segment s(1, 2, 3, 4);
    SUBCASE("SetA") {
      glm::vec2 newA(44, 55);
      s.setA(newA);
      CHECK_EQ(s.getA(), newA);
      CHECK_THROWS(s.setA(s.getB()));
    }
    SUBCASE("SetB") {
      glm::vec2 newB(44, 55);
      s.setB(newB);
      CHECK_EQ(s.getB(), newB);
      CHECK_THROWS(s.setB(s.getA()));
    }
  }
  SUBCASE("Testing normals") {
    SUBCASE("Horizontal segment") {
      Segment s(0, 2, 3, 2);
      auto normals = s.getNormals();
      if (normals.first.y > 0) {
        CHECK_EQ(normals.first, glm::vec2(0, 1));
        CHECK_EQ(normals.second, glm::vec2(0, -1));
      } else {
        CHECK_EQ(normals.first, glm::vec2(0, -1));
        CHECK_EQ(normals.second, glm::vec2(0, 1));
      }
    }
    SUBCASE("Vertical segment") {
      Segment s(2, 0, 2, 3);
      auto normals = s.getNormals();
      if (normals.first.x > 0) {
        CHECK_EQ(normals.first, glm::vec2(1, 0));
        CHECK_EQ(normals.second, glm::vec2(-1, 0));
      } else {
        CHECK_EQ(normals.first, glm::vec2(-1, 0));
        CHECK_EQ(normals.second, glm::vec2(1, 0));
      }
    }
    SUBCASE("Diagonal segment") {
      Segment s(0, 0, 3, 3);
      auto normals = s.getNormals();
      if (normals.first.x > 0) {
        CHECK_EQ(normals.first.x, doctest::Approx(std::cos(-M_PI_4)));
        CHECK_EQ(normals.first.y, doctest::Approx(std::sin(-M_PI_4)));
        CHECK_EQ(normals.second.x, doctest::Approx(std::cos(M_PI_4 + M_PI_2)));
        CHECK_EQ(normals.second.y, doctest::Approx(std::sin(M_PI_4 + M_PI_2)));
      } else {
        CHECK_EQ(normals.first.x, doctest::Approx(std::cos(M_PI_4 + M_PI_2)));
        CHECK_EQ(normals.first.y, doctest::Approx(std::sin(M_PI_4 + M_PI_2)));
        CHECK_EQ(normals.second.x, doctest::Approx(std::cos(-M_PI_4)));
        CHECK_EQ(normals.second.y, doctest::Approx(std::sin(-M_PI_4)));
      }
    }
  }
  SUBCASE("Testing getLineEquation") {
    SUBCASE("Horizontal segment") {
      Segment s(0, 2, 3, 2);
      auto equation = s.getLineEquation();
      CHECK_EQ(equation.gradient, 0);
      CHECK_EQ(equation.offset, 2);
    }
    SUBCASE("Vertical segment") {
      Segment s(2, 0, 2, 3);
      auto equation = s.getLineEquation();
      CHECK_EQ(equation.gradient, std::numeric_limits<double>::infinity());
      CHECK_EQ(equation.offset, std::numeric_limits<double>::infinity());
    }
    SUBCASE("Positive gradient segment") {
      Segment s(0, 2, 3, 8);
      auto equation = s.getLineEquation();
      CHECK_EQ(equation.gradient, 2);
      CHECK_EQ(equation.offset, 2);
    }
    SUBCASE("Negative gradient segment") {
      Segment s(0, -2, 3, -8);
      auto equation = s.getLineEquation();
      CHECK_EQ(equation.gradient, -2);
      CHECK_EQ(equation.offset, -2);
    }
  }
  SUBCASE("Testing length") {
    SUBCASE("Horizontal segment") {
      Segment s(0, 2, 3, 2);
      CHECK_EQ(s.length(), 3);
    }
    SUBCASE("Vertical segment") {
      Segment s(2, 0, 2, 3);
      CHECK_EQ(s.length(), 3);
    }
    SUBCASE("Diagonal segment") {
      Segment s(0, 0, std::cos(M_PI_4) * 3, std::sin(M_PI_4) * 3);
      CHECK_EQ(s.length(), doctest::Approx(3));
    }
  }
  SUBCASE("Testing couldContain") {
    SUBCASE("Couldn't contain") {
      CHECK_FALSE(Segment(0, 0, 10, 10).couldContain(glm::vec2(30, 11)));
      CHECK_FALSE(Segment(0, 0, 0, 10).couldContain(glm::vec2(30, 11)));
    }
    SUBCASE("Could contain") {
      CHECK(Segment(0, 0, 10, 10).couldContain(glm::vec2(5, 5)));
      CHECK(Segment(0, 0, 0, 10).couldContain(glm::vec2(0, 5)));
    }
  }
}