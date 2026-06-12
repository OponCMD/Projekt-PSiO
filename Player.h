#pragma once
#include "GameObject.h"
#include <SFML/Window/Event.hpp>

class Player : public GameObject {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    bool grounded;
    bool isGliding;
    bool isDucking;
    bool isSmashing;
    bool hasShield;

    float score;
    float glideTimer;

    sf::Clock tapClock;
    float lastSTime;

    void adjustShapeToState();

public:
    Player();

    void handleEvent(const sf::Event& event);
    void update(float dt, float scrollSpeed) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

    int getScore() const;
    void addScore(float s);
    void setScore(float s);
    bool getIsSmashing() const;
    bool getShield() const;
    void setShield(bool state);
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f p);
};