#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

// drag-with-mouse camera
class Camera {
public:
  Camera(sf::View view, float cameraSpeed, float zoomSpeed);
  void UpdateEvents(const sf::Event &event);
  void Update(float dt, sf::RenderWindow &window);
  const sf::View& GetView();

private:
  sf::View view;

  float cameraSpeed;
  float zoomSpeed;

  sf::Vector2i lastMouse;
  sf::Vector2i currentMouse;
};
