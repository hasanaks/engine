#include "Camera.hpp"
#include <SFML/Window/Event.hpp>

Camera::Camera(sf::View view, float cameraSpeed, float zoomSpeed)
  : view(view), cameraSpeed(cameraSpeed), zoomSpeed(zoomSpeed) {}

void Camera::UpdateEvents(const sf::Event &event) {
  if (event.type == sf::Event::MouseWheelScrolled) {
    const auto delta = 1 - event.mouseWheelScroll.delta * zoomSpeed;
    view.zoom(delta);
  }
}

void Camera::Update(float dt, sf::RenderWindow &window) {
  lastMouse = currentMouse;
  currentMouse = sf::Mouse::getPosition();

  auto mouseDelta = currentMouse - lastMouse;

  if (mouseDelta != sf::Vector2i{0, 0} && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    auto mouseDeltaf = sf::Vector2f{static_cast<float>(mouseDelta.x),
                                    static_cast<float>(mouseDelta.y)} *
                       dt * cameraSpeed;
    view.move(-mouseDeltaf);
  }

  window.setView(view);
}

const sf::View &Camera::GetView() {
  return view;
}
