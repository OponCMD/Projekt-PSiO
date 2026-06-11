#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
    void update(float dt, float scrollSpeed) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};
