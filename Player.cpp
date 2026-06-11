#include "Player.h"
#include "Config.h"

Player::Player() : velocity(0.f, 0.f), grounded(false), isGliding(false),
    isDucking(false), isSmashing(false), hasShield(false), score(0.f),
    glideTimer(0.f), lastSTime(-10.f) {
    shape.setSize(sf::Vector2f(60.f, 80.f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100.f, GROUND_Y - 80.f);
}

void Player::adjustShapeToState() {
    shape.setSize(sf::Vector2f(60.f, 80.f));
    shape.setFillColor(sf::Color::Green);
}

void Player::update(float dt, float scrollSpeed) {
    // Logika ruchu w Milestone 3
}

void Player::draw(sf::RenderWindow& window) { window.draw(shape); }
sf::FloatRect Player::getBounds() const { return shape.getGlobalBounds(); }

int Player::getScore() const { return static_cast<int>(score); }
void Player::addScore(float s) { score += s; }
void Player::setScore(float s) { score = s; }
