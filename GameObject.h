#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    bool markedForDeletion = false;

public:
    virtual ~GameObject() = default;
    virtual void update(float dt, float scrollSpeed) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;

    bool isMarkedForDeletion() const { return markedForDeletion; }
    void markForDeletion() { markedForDeletion = true; }
};