#include "window.hpp"

#define WINDOW_SIZE 700
#define WINDOW_PADDING 200

GraphicsWindow::GraphicsWindow(Simulation& simulation)
    : m_Window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Triangular Pool",
               sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(0, 0, 8)),
      m_SimulationGraphics(simulation),
      m_StatisticsGraphics(simulation),
      m_Simulation(simulation) {
  double maxCoordinate =
      std::max(simulation.getL(), std::max(simulation.getR1(), simulation.getR2()));
  m_SimulationGraphics.setPosition(WINDOW_PADDING, WINDOW_SIZE / 2);
  m_SimulationGraphics.setCoordsScaling((WINDOW_SIZE - WINDOW_PADDING * 2) / maxCoordinate);
  m_StatisticsGraphics.setPosition(10, 10);
  m_Simulation.addIterationEndedListener([this](auto particle) {  //
    this->m_Simulation.newIteration();                            //
  });                                                             //
}

void GraphicsWindow::show() {
  bool redraw = true;

  const double IDEAL_FRAMETIME = 1.0 / 60.0;

  while (m_Window.isOpen()) {
    const sf::Time elapsed = m_Clock.getElapsedTime();

    if (elapsed.asSeconds() >= IDEAL_FRAMETIME) {
      redraw = true;
      m_Simulation.update(elapsed.asMilliseconds());
      m_SimulationGraphics.update(elapsed);
      m_StatisticsGraphics.update(elapsed);
      m_Clock.restart();
    }

    processWindowEvents();

    if (redraw) {
      redraw = false;
      m_Window.clear(sf::Color(0x999999FF));
      m_Window.draw(m_SimulationGraphics);
      m_Window.draw(m_StatisticsGraphics);
      m_Window.display();
    }
  }
}

void GraphicsWindow::processWindowEvents() {
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