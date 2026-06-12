#include "Entities.h"
#include "Config.h"

void Obstacle::update(float dt, float scrollSpeed) {
    sprite.move(-scrollSpeed * dt, 0.f);
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) markForDeletion();
}

void Obstacle::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Obstacle::getBounds() const { return sprite.getGlobalBounds(); }

Barrier::Barrier(float startX, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(40.f / texSize.x, 60.f / texSize.y);
    }
    sprite.setPosition(startX, GROUND_Y - 60.f);
}

FlyingObstacle::FlyingObstacle(float startX, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(80.f / texSize.x, (GROUND_Y - 45.f) / texSize.y);
    }
    sprite.setPosition(startX, 0.f);
}

Pit::Pit(float startX, const sf::Texture& texture) : width(550.f) {
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(550.f / texSize.x, 22.f / texSize.y);
    }
    sprite.setPosition(startX, GROUND_Y - 2.f);
}

void Pit::update(float dt, float scrollSpeed) {
    sprite.move(-scrollSpeed * dt, 0.f);
    if (sprite.getPosition().x + width < 0) markForDeletion();
}

void Pit::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Pit::getBounds() const { return sprite.getGlobalBounds(); }