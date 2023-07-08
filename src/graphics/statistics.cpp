#include "statistics.hpp"

#include <sstream>

#include "../math/angles.hpp"
#include "../util/unused.hpp"
#include "font.hpp"

StatisticsGraphics::StatisticsGraphics(Simulation& simulation) : m_Simulation(simulation) {
  simulation.addIterationEndedListener([this](auto particle) { updateText(); });
  m_Labels.setFont(g_FontLucindaSansRegular);
  m_Labels.setColor(sf::Color::Black);
  m_Labels.setCharacterSize(15);

  std::stringstream out;
  out << "Number of iterations:\n";
  out << "Mean final Y:\n";
  out << "Mean final theta:\n";
  out << "Mean collisions per iteration:\n";
  out << "Std dev final Y:\n";
  out << "Std dev final theta:\n";
  out << "Skewness final y:\n";
  out << "Skewness final theta:\n";
  out << "Kurtosis final y:\n";
  out << "Kurtosis final theta:\n";
  m_Labels.setString(out.str());

  m_Values.setFont(g_FontLucindaSansRegular);
  m_Values.setColor(sf::Color::Red);
  m_Values.setCharacterSize(15);
  m_Values.setPosition(m_Labels.getLocalBounds().width + 10, 0);
  updateText();

  if (m_Simulation.getStats().getIterationsCount() == 0) {
    out.str(std::string());  // clear buffer
    out << "-\n";
    out << "-\n";
    out << "-\n";
    out << "-\n";
    out << "-\n";
    out << "-\n";
    out << "-\n";
    out << "-\n";
    out << "-\n";
    out << "-\n";
    m_Values.setString(out.str());
  }
}

void StatisticsGraphics::update(sf::Time const& elapsed) {
  UNUSED(elapsed);
  // nothing to do, the text is updated only on iteration ended
}

void StatisticsGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_Labels, states);
  target.draw(m_Values, states);
}

void StatisticsGraphics::updateText() {
  std::stringstream out;
  Statistics const& stats = m_Simulation.getStats();
  out << stats.getIterationsCount() << "\n";
  out << stats.getMeanFinalY() << "\n";
  out << degrees(stats.getMeanFinalTheta()) << "deg\n";
  out << stats.getMeanCollisions() << "\n";
  out << stats.getStdDevFinalY() << "\n";
  out << degrees(stats.getStdDevFinalTheta()) << "deg\n";
  out << stats.getSymmetryFinalY() << "\n";
  out << stats.getSymmetryFinalTheta() << "\n";
  out << stats.getFlatteningFinalY() << "\n";
  out << stats.getFlatteningFinalTheta() << "\n";
  m_Values.setString(out.str());
}
