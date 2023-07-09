#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <glm/vec2.hpp>
#include <vector>

namespace pool {

class Statistics {
 public:
  struct Entry {
    glm::vec2 initialPosition;
    float initialTheta;
    glm::vec2 finalPosition;
    float finalTheta;
    std::vector<glm::vec2> collisions;
  };

 private:
  std::vector<Entry> m_Entries;
  Entry m_CurrentEntry;
  float m_MeanFinalY;
  float m_MeanFinalTheta;
  float m_MeanCollisions;
  float m_StdDevFinalY;
  float m_StdDevFinalTheta;
  float m_SymmetryFinalY;
  float m_SymmetryFinalTheta;
  float m_FlatteningFinalY;
  float m_FlatteningFinalTheta;
  float m_FinalYSum;
  float m_FinalThetaSum;
  float m_CollisionsSum;

 public:
  Statistics();

  void createNewEntry(glm::vec2 const& initialPosition, float initialTheta);
  void addCollision(glm::vec2 const& collisionPoint);
  void commitEntry(glm::vec2 const& finalPosition, float finalTheta);
  void clear();
  std::vector<Entry> getEntries() const;
  Entry getCurrentEntry() const;
  int getIterationsCount() const;
  float getMeanFinalY() const;
  float getMeanFinalTheta() const;
  float getMeanCollisions() const;
  float getStdDevFinalY() const;
  float getStdDevFinalTheta() const;
  float getSymmetryFinalY() const;
  float getSymmetryFinalTheta() const;
  float getFlatteningFinalY() const;
  float getFlatteningFinalTheta() const;
  std::string toString(bool verbose = false) const;
  std::string toCSVString() const;

 private:
  void updateStats();
};

}  // namespace pool

#endif