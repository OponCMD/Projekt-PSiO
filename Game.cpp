#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;
    void render();
    void processEvents();

public:
    Game();
    void run();
};
