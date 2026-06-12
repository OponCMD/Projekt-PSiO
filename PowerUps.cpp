#include "PowerUps.h"

void PowerUp::update(float dt, float scrollSpeed) {
    sprite.move(-scrollSpeed * dt, 0.f);
    if (sprite.getPosition().x + width < 0) markForDeletion();
}

void PowerUp::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect PowerUp::getBounds() const { return sprite.getGlobalBounds(); }

ShieldPowerUp::ShieldPowerUp(float startX, float startY, const sf::Texture& texture) {
    width = 30.f;
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(30.f / texSize.x, 30.f / texSize.y);
    }
    sprite.setPosition(startX, startY);
}

ScorePowerUp::ScorePowerUp(float startX, float startY, const sf::Texture& texture) {
    width = 30.f;
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale(30.f / texSize.x, 30.f / texSize.y);
    }
    sprite.setPosition(startX, startY);
}