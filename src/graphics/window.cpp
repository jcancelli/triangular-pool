#include "window.hpp"

#define WINDOW_SIZE 700
#define WINDOW_PADDING 200

GraphicsWindow::GraphicsWindow(Simulation const& simulation)
    : m_Window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Triangular Pool",
               sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(0, 0, 8)),
      m_SimulationGraphics(simulation) {
  m_SimulationGraphics.setPosition(WINDOW_PADDING, WINDOW_SIZE / 2);
  double maxCoordinate =
      std::max(simulation.getL(), std::max(simulation.getR1(), simulation.getR2()));
  m_SimulationGraphics.setCoordinatesScaling((WINDOW_SIZE - WINDOW_PADDING * 2) / maxCoordinate);
}

void GraphicsWindow::show() {
  while (m_Window.isOpen()) {
    processEvents();
    m_Window.clear(sf::Color(0x999999FF));
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