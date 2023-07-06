#include "window.hpp"

GraphicsWindow::GraphicsWindow(unsigned width, unsigned height, Simulation const& simulation)
    : m_Window(sf::VideoMode(width, height), "Triangular Pool", sf::Style::Default,
               sf::ContextSettings(0, 0, 8)),
      m_SimulationGraphics(simulation) {
}

void GraphicsWindow::show() {
  while (m_Window.isOpen()) {
    processEvents();
    m_Window.clear(sf::Color::Black);
    m_Window.draw(m_SimulationGraphics);
    m_Window.display();
  }
}

void GraphicsWindow::processEvents() {
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