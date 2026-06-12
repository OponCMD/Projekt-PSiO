#include "Entities.h"
#include "Config.h"
#include <cstdlib>
#include <algorithm>

// ==========================================\
// BACKGROUND
// ==========================================\

Background::Background(sf::Texture& texture, float speedMult)
    : currentOffset(0.f), speedMultiplier(speedMult) {
    texture.setRepeated(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 800, 500));
    sprite.setPosition(0.f, 0.f);
}

void Background::update(float dt, float scrollSpeed) {
    currentOffset += scrollSpeed * speedMultiplier * dt;
    if (currentOffset > 800.f) currentOffset -= 800.f;
    sprite.setTextureRect(sf::IntRect(static_cast<int>(currentOffset), 0, 800, 500));
}

void Background::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Background::getBounds() const { return sf::FloatRect(); }

// ==========================================\
// GROUND
// ==========================================\

Ground::Ground(sf::Texture& texture, float speedMult)
    : currentOffset(0.f), speedMultiplier(speedMult) {
    texture.setRepeated(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 800, 100));
    sprite.setPosition(0.f, GROUND_Y);
}

void Ground::update(float dt, float scrollSpeed) {
    currentOffset += scrollSpeed * speedMultiplier * dt;
    if (currentOffset > 800.f) currentOffset -= 800.f;
    sprite.setTextureRect(sf::IntRect(static_cast<int>(currentOffset), 0, 800, 100));
}

void Ground::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Ground::getBounds() const { return sf::FloatRect(); }

// ==========================================\
// OBSTACLE BASE
// ==========================================\

void Obstacle::update(float dt, float scrollSpeed) {
    sprite.move(-scrollSpeed * dt, 0.f);
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) {
        markForDeletion();
    }
}

void Obstacle::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Obstacle::getBounds() const { return sprite.getGlobalBounds(); }

// ==========================================\
// BARRIER
// ==========================================\

Barrier::Barrier(float startX, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(40.f / texSize.x, 60.f / texSize.y);
    }
    sprite.setPosition(startX, GROUND_Y - 60.f);
}

// ==========================================\
// FLYING OBSTACLE
// ==========================================\

FlyingObstacle::FlyingObstacle(float startX, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(80.f / texSize.x, (GROUND_Y - 45.f) / texSize.y);
    }
    sprite.setPosition(startX, 0.f);
}

// ==========================================\
// PIT
// ==========================================\

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