#pragma once
#include "GameObject.h"
#include <SFML/Window/Event.hpp>
#include <vector>

class Player : public GameObject {
private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Sprite shieldSprite;
    sf::Vector2f velocity;

    bool grounded;
    bool hasShield;

    float score;

    std::vector<sf::Texture> runTextures;
    sf::Texture shieldTexture;

    size_t currentFrame;
    float animationTimer;
    const float FRAME_TIME = 0.12f;

    void adjustShapeToState();

public:
    Player(const std::vector<sf::Texture>& runTex, const sf::Texture& shieldTex);

    void handleEvent(const sf::Event& event);
    void update(float dt, float scrollSpeed) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

    int getScore() const;
    void addScore(float s);
    void setScore(float s);
    bool getShield() const;
    void setShield(bool state);
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f p);
};