#include "Math.hpp"
#include "PhysicsWorld.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
#include <utility>

int main() {
  sf::RenderWindow window(sf::VideoMode(1200, 800), "engine");
  window.setVerticalSyncEnabled(true);

  if (ImGui::SFML::Init(window) != true) {
    std::cerr << "imgui sfml init fail" << std::endl;
    return 1;
  }

  std::shared_ptr<PhysicsObject> selectedObject;
  std::unordered_set<std::shared_ptr<PhysicsObject>> objects;

  PhysicsWorld physicsWorld({0, 10.f});

  const float physicsTimeStep = 0.02f;
  float physicsAccumulator = 0;

  bool simulationRunning = true;

  sf::Clock dtClock;
  while (window.isOpen()) {
    const auto deltaTime = dtClock.restart();

    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // create object at the mouse's position
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
          if (sf::Keyboard::isKeyPressed(
                  sf::Keyboard::LControl)) { // move an object
            if (const auto &it = std::find_if(
                    objects.cbegin(), objects.cend(),
                    [&window,
                     &event](const std::shared_ptr<PhysicsObject> &object) {
                      if (const auto &collider = object->rectangleCollider) {
                        sf::FloatRect rect(
                            sf::Vector2f{object->position.x(),
                                         object->position.y()},
                            sf::Vector2f{collider->dimensions.x(),
                                         collider->dimensions.y()});

                        if (rect.contains(event.mouseButton.x, event.mouseButton.y)) {
                          return true;
                        }
                      }

                      return false;
                    });
                it != objects.cend()) {
              selectedObject = *it;
            }
          } else { // create object at mouse position
            const auto mousePosition = sf::Vector2i{event.mouseButton.x, event.mouseButton.y};

            const auto object = std::make_shared<PhysicsObject>();
            object->rectangleCollider = RectangleCollider{{100, 100}};
            object->position = Vector2f{mousePosition.x, mousePosition.y};
            object->mass = 1;

            objects.insert(object);
            physicsWorld.AddPhysicsObject(object);
          }
        }
      }

      if (event.type == sf::Event::MouseButtonReleased) {
        if (selectedObject) {
          selectedObject->force +=
              selectedObject->position -
              Vector2f{event.mouseButton.x, event.mouseButton.y};
        }

        selectedObject = nullptr;
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
          simulationRunning = !simulationRunning;
        }
      }
    }

    if (selectedObject != nullptr &&
        selectedObject->rectangleCollider.has_value()) {
      const auto mousePosition = sf::Mouse::getPosition();

      selectedObject->force +=
          ((Vector2f{mousePosition.x, mousePosition.y} -
            selectedObject->rectangleCollider->dimensions) -
           selectedObject->position) *
          deltaTime.asSeconds() * 400;
    }

    if (simulationRunning) {
      // step physics
      physicsAccumulator += deltaTime.asSeconds();
    }

    std::vector<PhysicsObject> lastState;

    if (physicsAccumulator < physicsTimeStep) {
      lastState = physicsWorld.CopyState();
    }

    while (physicsAccumulator >= physicsTimeStep) {
      if (physicsAccumulator - physicsTimeStep < physicsTimeStep) {
        lastState = physicsWorld.CopyState();
      }

      physicsWorld.Step(physicsTimeStep);
      physicsAccumulator -= physicsTimeStep;
    }

    const auto currentState = physicsWorld.CopyState();

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

    window.clear();

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

    // imgui
    ImGui::SFML::Update(window, deltaTime);

    ImGui::Begin("Info");
    if (simulationRunning) {
      ImGui::Text("Running");
    } else {
      ImGui::Text("Stopped");
    }
    ImGui::Text("Remaining object(s): %ld", currentState.size());
    ImGui::End();

    ImGui::SFML::Render(window);

    window.display();
  }

  ImGui::SFML::Shutdown();
}
