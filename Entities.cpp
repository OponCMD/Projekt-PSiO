#include "Entities.h"
#include "Config.h"

void Obstacle::update(float dt, float scrollSpeed) {
    shape.move(-scrollSpeed * dt, 0.f);
    if (shape.getPosition().x + shape.getSize().x < 0) markForDeletion();
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Obstacle::getBounds() const {
    return shape.getGlobalBounds();
}

Barrier::Barrier(float startX) {
    shape.setSize(sf::Vector2f(40.f, 60.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startX, GROUND_Y - 60.f);
}

FlyingObstacle::FlyingObstacle(float startX) {
    shape.setSize(sf::Vector2f(80.f, GROUND_Y - 45.f));
    shape.setFillColor(sf::Color(150, 0, 0));
    shape.setPosition(startX, 0.f);
}

Pit::Pit(float startX) {
    shape.setSize(sf::Vector2f(550.f, 22.f));
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(startX, GROUND_Y - 2.f);
}