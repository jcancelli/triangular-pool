#include "statistics.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <sstream>

#include "math/angles.hpp"
#include "math/statistics.hpp"

namespace pool {

Statistics::Statistics()
    : m_MeanFinalY{0.0},
      m_MeanFinalTheta{0.0},
      m_MeanCollisions{0.0},
      m_StdDevFinalY{0.0},
      m_StdDevFinalTheta{0.0},
      m_SymmetryFinalY{0.0},
      m_SymmetryFinalTheta{0.0},
      m_FlatteningFinalY{0.0},
      m_FlatteningFinalTheta{0.0},
      m_FinalYSum{0.0},
      m_FinalThetaSum{0.0},
      m_CollisionsSum{0.0} {
}

void Statistics::createNewEntry(glm::vec2 const& initialPosition, float initialTheta) {
  m_CurrentEntry = Entry();
  m_CurrentEntry.initialPosition = initialPosition;
  m_CurrentEntry.initialTheta = initialTheta;
}

void Statistics::addCollision(glm::vec2 const& collisionPoint) {
  m_CurrentEntry.collisions.push_back(collisionPoint);
}

void Statistics::commitEntry(glm::vec2 const& finalPosition, float finalTheta) {
  m_CurrentEntry.finalPosition = finalPosition;
  m_CurrentEntry.finalTheta = finalTheta;
  m_Entries.push_back(m_CurrentEntry);
  updateStats();
}

void Statistics::clear() {
  m_Entries.clear();
  m_CurrentEntry = Entry();
}

std::vector<Statistics::Entry> Statistics::getEntries() const {
  return m_Entries;
}

Statistics::Entry Statistics::getCurrentEntry() const {
  return m_CurrentEntry;
}

int Statistics::getIterationsCount() const {
  return m_Entries.size();
}

float Statistics::getMeanFinalY() const {
  return m_MeanFinalY;
}

float Statistics::getMeanFinalTheta() const {
  return m_MeanFinalTheta;
}

float Statistics::getMeanCollisions() const {
  return m_MeanCollisions;
}

float Statistics::getStdDevFinalY() const {
  return m_StdDevFinalY;
}

float Statistics::getStdDevFinalTheta() const {
  return m_StdDevFinalTheta;
}

float Statistics::getSymmetryFinalY() const {
  return m_SymmetryFinalY;
}

float Statistics::getSymmetryFinalTheta() const {
  return m_SymmetryFinalTheta;
}

float Statistics::getFlatteningFinalY() const {
  return m_FlatteningFinalY;
}

float Statistics::getFlatteningFinalTheta() const {
  return m_FlatteningFinalTheta;
}

std::string Statistics::toString(bool verbose) const {
  std::stringstream out;
  out << "------Stats ------\n";
  out << "N:\t\t\t" << getIterationsCount() << "\t\t\tNumber of iterations\n";

  out << "mean Y:\t\t\t" << getMeanFinalY() << "\t\tMean final Y\n";
  out << "mean theta:\t\t" << math::degrees(getMeanFinalTheta())
      << "°\t\tMean final particle direction angle\n";
  out << "mean collisions:\t" << getMeanCollisions()
      << "\t\tMean number of collisions per iteration\n";

  out << "stddev y:\t\t" << getStdDevFinalY() << "\t\tStandard deviation final Y\n";
  out << "stddev theta:\t\t" << math::degrees(getStdDevFinalTheta())
      << "°\t\tStandard deviation final particle direction angle\n";

  out << "sym Y:\t\t\t" << getSymmetryFinalY() << "\t\tSymmetry coefficient final Y\n";
  out << "sym theta:\t\t" << getSymmetryFinalTheta()
      << "\t\tSymmetry coefficient final particle direction angle\n";

  out << "flat Y:\t\t\t" << getFlatteningFinalY() << "\t\tFlattening coefficient final Y\n";
  out << "flat theta:\t\t" << getFlatteningFinalTheta()
      << "\t\tFlattening coefficient final particle direction angle\n";

  if (verbose) {
    int i = 1;
    out << "------ Details ------\n";
    for (auto const& entry : m_Entries) {
      out << "Iteration #" << i << "\n";
      out << "\tInitial position:\t" << entry.initialPosition << "\n";
      out << "\tInitial theta:\t\t" << math::degrees(entry.initialTheta) << "°\n";
      out << "\tFinal position:\t\t" << entry.finalPosition << "\n";
      out << "\tFinal theta:\t\t" << math::degrees(entry.finalTheta) << "°\n";

      out << "\tCollisions:\n";
      for (auto const& collision : entry.collisions) {
        out << "\t\t" << collision << "\n";
      }

      i++;
    }
  }
  return out.str();
}

std::string Statistics::toCSVString() const {
  std::stringstream out;
  out << getIterationsCount() << ";";
  out << getMeanFinalY() << ";";
  out << math::degrees(getMeanFinalTheta()) << ";";
  out << getMeanCollisions() << ";";
  out << getStdDevFinalY() << ";";
  out << math::degrees(getStdDevFinalTheta()) << ";";
  out << getSymmetryFinalY() << ";";
  out << getSymmetryFinalTheta() << ";";
  out << getFlatteningFinalTheta() << ";";
  out << getFlatteningFinalY();
  return out.str();
}

void Statistics::updateStats() {
  m_FinalYSum += m_CurrentEntry.finalPosition.y;
  m_FinalThetaSum += m_CurrentEntry.finalTheta;
  m_CollisionsSum += m_CurrentEntry.collisions.size();

  const int n = getIterationsCount();

  m_MeanFinalY = m_FinalYSum / n;
  m_MeanFinalTheta = m_FinalThetaSum / n;
  m_MeanCollisions = m_CollisionsSum / n;

  if (n < 2) {
    return;
  }

  std::vector<float> yValues, thetaValues;
  yValues.resize(n);
  thetaValues.resize(n);
  auto mapToFinalY = [](auto entry) { return entry.finalPosition.y; };
  std::transform(m_Entries.cbegin(), m_Entries.cend(), yValues.begin(), mapToFinalY);
  auto mapToFinalTheta = [](auto entry) { return entry.finalTheta; };
  std::transform(m_Entries.cbegin(), m_Entries.cend(), thetaValues.begin(), mapToFinalTheta);

  m_StdDevFinalY = math::stdDev(yValues, m_MeanFinalY);
  m_StdDevFinalTheta = math::stdDev(thetaValues, m_MeanFinalTheta);

  m_SymmetryFinalY = math::skewness(yValues, m_MeanFinalY, m_StdDevFinalY);
  m_SymmetryFinalTheta = math::skewness(thetaValues, m_MeanFinalTheta, m_StdDevFinalTheta);

  m_FlatteningFinalY = math::kurtosis(yValues, m_MeanFinalY, m_StdDevFinalY);
  m_FlatteningFinalTheta = math::kurtosis(thetaValues, m_MeanFinalTheta, m_StdDevFinalTheta);
}

}  // namespace pool