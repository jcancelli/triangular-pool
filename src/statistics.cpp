#include "statistics.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

#include "math/angles.hpp"
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
      m_FinalThetaSum{0.0},
      m_VerboseOutput{true} {
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

void Statistics::setVerboseOutput(bool verbose) {
  m_VerboseOutput = verbose;
}

bool Statistics::isVerboseOutput() const {
  return m_VerboseOutput;
}

void Statistics::updateStats() {
  m_FinalYSum += m_CurrentEntry.finalPosition.y;
  m_FinalThetaSum += m_CurrentEntry.finalTheta;

  const int n = m_Entries.size();

  m_MeanFinalY = m_FinalYSum / n;
  m_MeanFinalTheta = m_FinalThetaSum / n;

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

  m_StdDevFinalY = stdDev(yValues, m_MeanFinalY);
  m_StdDevFinalTheta = stdDev(thetaValues, m_MeanFinalTheta);

  m_SymmetryFinalY = skewness(yValues, m_MeanFinalY, m_StdDevFinalY);
  m_SymmetryFinalTheta = skewness(thetaValues, m_MeanFinalTheta, m_StdDevFinalTheta);

  m_FlatteningFinalY = kurtosis(yValues, m_MeanFinalY, m_StdDevFinalY);
  m_FlatteningFinalTheta = kurtosis(thetaValues, m_MeanFinalTheta, m_StdDevFinalTheta);
}

std::ostream& operator<<(std::ostream& os, Statistics const& stats) {
  const auto entries = stats.getEntries();

  os << "N:\t\t" << stats.getIterationsCount() << "\t\tNumber of iterations\n";

  os << "mean Y:\t\t" << stats.getMeanFinalY() << "\t\tMean final Y\n";
  os << "stddev y:\t" << stats.getStdDevFinalY() << "\t\tStandard deviation final Y\n";
  os << "sym Y:\t\t" << stats.getSymmetryFinalY() << "\t\tSymmetry coefficient final Y\n";
  os << "flat Y:\t\t" << stats.getFlatteningFinalY() << "\t\tFlattening coefficient final Y\n";

  os << "mean theta:\t" << degrees(stats.getMeanFinalTheta())
     << "°\t\tMean final particle direction angle\n";
  os << "stddev theta:\t" << degrees(stats.getStdDevFinalTheta())
     << "°\t\tStandard deviation final particle direction angle\n";
  os << "sym theta:\t" << stats.getSymmetryFinalTheta()
     << "\t\tSymmetry coefficient final particle direction angle\n";
  os << "flat theta:\t" << stats.getFlatteningFinalTheta()
     << "\t\tFlattening coefficient final particle direction angle\n";

  if (stats.isVerboseOutput()) {
    int i = 1;
    os << "------ Details ------\n";
    for (auto const& entry : entries) {
      os << "Iteration #" << i << "\n";
      os << "\tInitial position:\t" << entry.initialPosition << "\n";
      os << "\tInitial theta:\t\t" << degrees(entry.initialTheta) << "°\n";
      os << "\tFinal position:\t\t" << entry.finalPosition << "\n";
      os << "\tFinal theta:\t\t" << degrees(entry.finalTheta) << "°\n";

      os << "\tCollisions:\n";
      for (auto const& collision : entry.collisions) {
        os << "\t\t" << collision << "\n";
      }

      i++;
    }
  }
  return os;
}