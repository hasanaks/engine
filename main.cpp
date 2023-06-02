#include "Camera.hpp"
#include "World.hpp"
#include "Math.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(1200, 800), "engine");
  window.setVerticalSyncEnabled(true);

  if (ImGui::SFML::Init(window) != true) {
    std::cerr << "imgui sfml init fail" << std::endl;
    return 1;
  }

  Camera camera(window.getDefaultView(), 20, 0.005f);

  World world({0, 10.f});

  const float physicsTimeStep = 0.02f;
  float physicsAccumulator = 0;

  sf::Clock dtClock;
  while (window.isOpen()) {
    const auto deltaTime = dtClock.restart();

    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);
      camera.UpdateEvents(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // create object at the mouse's position
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
          const auto mousePosition = window.mapPixelToCoords(
              sf::Vector2i{event.mouseButton.x, event.mouseButton.y});

          const auto object = std::make_shared<PhysicsObject>();
          object->rectangleCollider = RectangleCollider{{100, 100}};
          object->position = Vector2f{mousePosition.x, mousePosition.y};
          object->mass = 1;

          world.AddPhysicsObject(object);
        }
      }
    }

    if (!ImGui::GetIO().WantCaptureMouse) {
      camera.Update(deltaTime.asSeconds(), window);
    }

    // step physics
    physicsAccumulator += deltaTime.asSeconds();

    std::vector<PhysicsObject> lastState;

    if (physicsAccumulator < physicsTimeStep) {
      lastState = world.CopyState();
    }

    while (physicsAccumulator >= physicsTimeStep) {
      if (physicsAccumulator - physicsTimeStep < physicsTimeStep) {
        lastState = world.CopyState();
      }

      world.Step(physicsTimeStep);
      physicsAccumulator -= physicsTimeStep;
    }

    const auto currentState = world.CopyState();

    // imgui
    ImGui::SFML::Update(window, deltaTime);

    ImGui::Begin("Info");
    ImGui::Text("Remaining object(s): %ld", currentState.size());
    ImGui::End();

    window.clear();

    // interpolate last and current state
    const auto alpha = physicsAccumulator / physicsTimeStep;
    std::vector<PhysicsObject> state(currentState.size());

    std::transform(currentState.cbegin(), currentState.cend(),
                   lastState.cbegin(), state.begin(),
                   [alpha](const auto &p1, const auto &p2) {
                     auto object = p2;
                     object.position = Lerp(p1.position, p2.position, alpha);
                     return p2;
                   });

    // render objects
    for (const auto &object : state) {
      if (const auto &collider = object.rectangleCollider) {
        sf::RectangleShape rect(
            {collider->dimensions.x(), collider->dimensions.y()});
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(4);
        rect.setFillColor(sf::Color::Black);

        rect.setPosition({object.position.x(), object.position.y()});
        window.draw(rect);
      }
    }

    ImGui::SFML::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
}
