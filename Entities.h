#pragma once
#include "GameObject.h"

class Obstacle : public GameObject {
protected:
    sf::RectangleShape shape;
public:
    void update(float dt, float scrollSpeed) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};

class Barrier : public Obstacle {
public:
    Barrier(float startX);
};

class FlyingObstacle : public Obstacle {
public:
    FlyingObstacle(float startX);
};

class Pit : public Obstacle {
public:
    Pit(float startX);
};
