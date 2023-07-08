#include "statistics.hpp"

#include <sstream>

#include "../math/angles.hpp"
#include "../util/unused.hpp"
#include "font.hpp"

StatisticsGraphics::StatisticsGraphics(Simulation& simulation) : m_Simulation(simulation) {
  simulation.addIterationEndedListener([this](auto particle) { updateText(); });
  m_Text.setFont(g_FontLucindaSansRegular);
  m_Text.setColor(sf::Color::Black);
  m_Text.setCharacterSize(15);
  updateText();
}

void StatisticsGraphics::update(sf::Time const& elapsed) {
  UNUSED(elapsed);
  // nothing to do, the text is updated only on iteration ended
}

void StatisticsGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_Text, states);
}

void StatisticsGraphics::updateText() {
  std::stringstream out;
  Statistics stats = m_Simulation.getStats();
  out << "Mean final Y: " << stats.getMeanFinalY() << "\n";
  out << "Mean final theta: " << degrees(stats.getMeanFinalTheta()) << "deg\n";
  out << "Std dev final Y: " << stats.getStdDevFinalY() << "\n";
  out << "Std dev final theta: " << degrees(stats.getStdDevFinalTheta()) << "deg\n";
  out << "Skewness final y: " << stats.getSymmetryFinalY() << "\n";
  out << "Skewness final theta: " << stats.getSymmetryFinalTheta() << "\n";
  out << "Kurtosis final y: " << stats.getFlatteningFinalY() << "\n";
  out << "Kurtosis final theta: " << stats.getFlatteningFinalTheta() << "\n";
  m_Text.setString(out.str());
}
