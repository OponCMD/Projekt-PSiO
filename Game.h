#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;

    void processEvents();
    void update(float dt);
    void render();

public:
    Game();
    void run();
};
