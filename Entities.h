#pragma once
#include "GameObject.h"

class Obstacle : public GameObject {
protected:
    sf::Sprite sprite;
public:
    void update(float dt, float scrollSpeed) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};

class Barrier : public Obstacle {
public:
    Barrier(float startX, const sf::Texture& texture);
};

class FlyingObstacle : public Obstacle {
public:
    FlyingObstacle(float startX, const sf::Texture& texture);
};

class Pit : public GameObject {
private:
    sf::Sprite sprite;
    float width;
public:
    Pit(float startX, const sf::Texture& texture);
    void update(float dt, float scrollSpeed) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};