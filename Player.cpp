#include "Player.h"
#include "Config.h"
#include <cmath>

Player::Player(const std::vector<sf::Texture>& runTex, const sf::Texture& jumpTex,
               const sf::Texture& glidTex, const sf::Texture& shieldTex)
    : velocity(0.f, 0.f), grounded(false), isGliding(false), hasShield(false), score(0.f),
    glideTimer(0.f), runTextures(runTex), jumpUpTexture(jumpTex), glideTexture(glidTex),
    shieldTexture(shieldTex), currentFrame(0), animationTimer(0.f) {

    shape.setSize(sf::Vector2f(60.f, 80.f));
    shape.setPosition(100.f, GROUND_Y - 80.f);

    if (!runTextures.empty()) sprite.setTexture(runTextures[currentFrame]);
    shieldSprite.setTexture(shieldTexture);
    adjustShapeToState();
}

void Player::adjustShapeToState() {
    shape.setSize(sf::Vector2f(60.f, 80.f));
    sprite.setColor(sf::Color::White);

    if (sprite.getTexture()) {
        sf::Vector2u texSize = sprite.getTexture()->getSize();
        sprite.setOrigin(texSize.x / 2.f, static_cast<float>(texSize.y));
        float scaleX = shape.getSize().x / texSize.x;
        float scaleY = shape.getSize().y / texSize.y;
        sprite.setScale(scaleX, scaleY);
    }

    if (shieldSprite.getTexture()) {
        sf::Vector2u shieldTexSize = shieldSprite.getTexture()->getSize();
        shieldSprite.setOrigin(shieldTexSize.x / 2.f, shieldTexSize.y / 2.f);
        float shieldScaleX = (shape.getSize().x * 1.4f) / shieldTexSize.x;
        float shieldScaleY = (shape.getSize().y * 1.3f) / shieldTexSize.y;
        shieldSprite.setScale(shieldScaleX, shieldScaleY);
        shieldSprite.setColor(sf::Color(255, 255, 255, 150));
    }
}

void Player::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            if (grounded) {
                velocity.y = JUMP_VELOCITY;
                grounded = false;
                glideTimer = MAX_GLIDE_TIME;
            } else if (glideTimer > 0.f) {
                isGliding = true;
            }
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W) isGliding = false;
    }
}

void Player::update(float dt, float scrollSpeed) {
    velocity.x = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x = -PLAYER_HORIZ_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x = PLAYER_HORIZ_SPEED;

    if (!grounded) {
        if (isGliding && glideTimer > 0.f) {
            velocity.y = 0.f;
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
        isGliding = false;
        glideTimer = MAX_GLIDE_TIME;
    } else {
        grounded = false;
    }

    if (pos.x < 0) pos.x = 0;
    if (pos.x > 800.f - shape.getSize().x) pos.x = 800.f - shape.getSize().x;
    shape.setPosition(pos);

    if (!grounded) {
        if (isGliding || std::abs(velocity.y) < 100.f) sprite.setTexture(glideTexture, true);
        else if (velocity.y < -100.f) sprite.setTexture(jumpUpTexture, true);
        else if (!runTextures.empty()) sprite.setTexture(runTextures[0], true);
    } else {
        if (!runTextures.empty()) {
            animationTimer += dt;
            if (animationTimer >= FRAME_TIME) {
                animationTimer = 0.f;
                currentFrame = (currentFrame + 1) % runTextures.size();
            }
            sprite.setTexture(runTextures[currentFrame], true);
        }
    }

    sprite.setPosition(shape.getPosition().x + shape.getSize().x / 2.f, shape.getPosition().y + shape.getSize().y);
    shieldSprite.setPosition(shape.getPosition().x + shape.getSize().x / 2.f, shape.getPosition().y + shape.getSize().y / 2.f);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    if (hasShield) window.draw(shieldSprite);
}

sf::FloatRect Player::getBounds() const { return shape.getGlobalBounds(); }
int Player::getScore() const { return static_cast<int>(score); }
void Player::addScore(float s) { score += s; }
void Player::setScore(float s) { score = s; }
bool Player::getShield() const { return hasShield; }
void Player::setShield(bool state) { hasShield = state; adjustShapeToState(); }
sf::Vector2f Player::getPosition() const { return shape.getPosition(); }
void Player::setPosition(sf::Vector2f p) { shape.setPosition(p); }