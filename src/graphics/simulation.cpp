#include "simulation.hpp"

SimulationGraphics::SimulationGraphics(unsigned width, unsigned height, std::string const& title,
                                       unsigned antialiasing)
    : m_Window(sf::VideoMode(width, height), title, sf::Style::Default,
               sf::ContextSettings(0, 0, antialiasing)) {
}

void SimulationGraphics::show() {
  while (m_Window.isOpen()) {
    processEvents();
    m_Window.clear(sf::Color::Black);
    m_Window.display();
  }
}

void SimulationGraphics::processEvents() {
  sf::Event event;
  while (m_Window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        m_Window.close();
        break;
      default:
        // do nothing
        break;
    }
  }
}