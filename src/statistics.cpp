#include "statistics.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

#include "math/statistics.hpp"

Statistics::Statistics()
    : m_MeanFinalY{0.0},
      m_MeanFinalTheta{0.0},
      m_StdDevFinalY{0.0},
      m_StdDevFinalTheta{0.0},
      m_SymmetryFinalY{0.0},
      m_SymmetryFinalTheta{0.0},
      m_FlatteningFinalY{0.0},
      m_FlatteningFinalTheta{0.0},
      m_FinalYSum{0.0},
      m_FinalThetaSum{0.0} {
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

float Statistics::getMeanFinalY() const {
  return m_MeanFinalY;
}

float Statistics::getMeanFinalTheta() const {
  return m_MeanFinalTheta;
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

void Statistics::updateStats() {
  m_FinalYSum += m_CurrentEntry.finalPosition.y;
  m_FinalThetaSum += m_CurrentEntry.finalTheta;

  const int n = m_Entries.size();

  m_MeanFinalY = m_FinalYSum / n;
  m_MeanFinalTheta = m_FinalThetaSum / n;

  std::vector<float> yValues, thetaValues;
  yValues.resize(n);
  thetaValues.resize(n);
  auto mapToFinalY = [](auto entry) { return entry.finalPosition.y; };
  std::transform(m_Entries.cbegin(), m_Entries.cend(), yValues.begin(), mapToFinalY);
  auto mapToFinalTheta = [](auto entry) { return entry.finalTheta; };
  std::transform(m_Entries.cbegin(), m_Entries.cend(), thetaValues.begin(), mapToFinalTheta);

  m_StdDevFinalY = stdDev(yValues, m_MeanFinalY);
  m_StdDevFinalTheta = stdDev(thetaValues, m_MeanFinalTheta);

  // TODO: implement symmetry coef
  // TODO: implement flattening coef
}

std::ostream& operator<<(std::ostream& os, Statistics const& stats) {
  const auto entries = stats.getEntries();

  os << "N:\t" << entries.size() << "\tNumber of iterations\n";

  os << "mean Y:\t" << stats.getMeanFinalY() << "\tMean final Y\n";
  os << "stddev y:\t" << stats.getStdDevFinalY() << "\tStandard deviation final Y\n";
  os << "sym Y:\t" << stats.getSymmetryFinalY() << "\tSymmetry coefficient final Y\n";
  os << "flat Y:\t" << stats.getFlatteningFinalY() << "\tFlattening coefficient final Y\n";

  os << "mean theta:\t" << stats.getMeanFinalTheta() << "\tMean final particle direction angle\n";
  os << "stddev theta:\t" << stats.getStdDevFinalTheta()
     << "\tStandard deviation final particle direction angle\n";
  os << "sym theta:\t" << stats.getSymmetryFinalTheta()
     << "\tSymmetry coefficient final particle direction angle\n";
  os << "flat theta:\t" << stats.getFlatteningFinalTheta()
     << "\tFlattening coefficient final particle direction angle\n";

  int i = 1;
  os << "Details:\n";
  for (auto const& entry : entries) {
    os << "Symulation #" << i << "\n";
    os << "\tInitial position:\t" << entry.initialPosition << "\n";
    os << "\tInitial theta:\t" << entry.initialTheta << "\n";
    os << "\tFinal position:\t" << entry.finalPosition << "\n";
    os << "\tFinal theta:\t" << entry.finalTheta << "\n";

    os << "\tCollisions:\n";
    for (auto const& collision : entry.collisions) {
      os << "\t\t" << collision << "\n";
    }

    i++;
  }
}