#pragma once
#include "GameObject.h"

class PowerUp : public GameObject {
protected:
    sf::CircleShape shape;
public:
    void update(float dt, float scrollSpeed) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};

class ShieldPowerUp : public PowerUp {
public:
    ShieldPowerUp(float startX, float startY);
};

class ScorePowerUp : public PowerUp {
public:
    ScorePowerUp(float startX, float startY);
};
