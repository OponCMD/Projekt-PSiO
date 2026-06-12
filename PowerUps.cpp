#include "PowerUps.h"

void PowerUp::update(float dt, float scrollSpeed) {
    shape.move(-scrollSpeed * dt, 0.f);
    if (shape.getPosition().x + shape.getRadius() * 2 < 0) markForDeletion();
}

void PowerUp::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect PowerUp::getBounds() const {
    return shape.getGlobalBounds();
}

ShieldPowerUp::ShieldPowerUp(float startX, float startY) {
    shape.setRadius(15.f);
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(startX, startY);
}

ScorePowerUp::ScorePowerUp(float startX, float startY) {
    shape.setRadius(15.f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startX, startY);
}