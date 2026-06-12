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
    if (isDucking || isSmashing) {
        shape.setSize(sf::Vector2f(60.f, 40.f));
        shape.setFillColor(isSmashing ? sf::Color::Red : sf::Color::Magenta);
    } else {
        shape.setSize(sf::Vector2f(60.f, 80.f));
        shape.setFillColor(hasShield ? sf::Color::Cyan : sf::Color::Green);
    }
}

void Player::handleEvent(const sf::Event& event) {
    float currentTime = tapClock.getElapsedTime().asSeconds();

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            if (grounded) {
                velocity.y = JUMP_VELOCITY;
                grounded = false;
                glideTimer = MAX_GLIDE_TIME;
            } else {
                if (glideTimer > 0.f) {
                    isGliding = true;
                }
            }
        }
        if (event.key.code == sf::Keyboard::S) {
            if (grounded) {
                isDucking = true;
            } else {
                if (currentTime - lastSTime <= DOUBLE_TAP_TIME) {
                    isSmashing = true;
                    isGliding = false;
                    velocity.y = SMASH_VELOCITY;
                }
            }
            lastSTime = currentTime;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W) isGliding = false;
        if (event.key.code == sf::Keyboard::S) isDucking = false;
    }
}

void Player::update(float dt, float scrollSpeed) {
    velocity.x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x = -PLAYER_HORIZ_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x = PLAYER_HORIZ_SPEED;

    if (!grounded) {
        if (isGliding && glideTimer > 0.f) {
            velocity.y = 0.f; // Zatrzymanie w powietrzu
            glideTimer -= dt;
        } else {
            isGliding = false;
            velocity.y += GRAVITY * dt;
        }
    }

    shape.move(velocity.x * dt, velocity.y * dt);
    sf::Vector2f pos = shape.getPosition();

    adjustShapeToState();
    if (pos.y + shape.getSize().y >= GROUND_Y) {
        pos.y = GROUND_Y - shape.getSize().y;
        velocity.y = 0;
        grounded = true;
        isSmashing = false;
        isGliding = false;
        glideTimer = MAX_GLIDE_TIME;
    } else {
        grounded = false;
    }

    if (pos.x < 0) pos.x = 0;
    if (pos.x > 800.f - shape.getSize().x) pos.x = 800.f - shape.getSize().x;
    shape.setPosition(pos);
}

void Player::draw(sf::RenderWindow& window) { window.draw(shape); }
sf::FloatRect Player::getBounds() const { return shape.getGlobalBounds(); }

int Player::getScore() const { return static_cast<int>(score); }
void Player::addScore(float s) { score += s; }
void Player::setScore(float s) { score = s; }
bool Player::getIsSmashing() const { return isSmashing; }
bool Player::getShield() const { return hasShield; }
void Player::setShield(bool state) { hasShield = state; adjustShapeToState(); }
sf::Vector2f Player::getPosition() const { return shape.getPosition(); }
void Player::setPosition(sf::Vector2f p) { shape.setPosition(p); }
