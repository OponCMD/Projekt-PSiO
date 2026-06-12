#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameObject.h"

class Player;

class Game {
private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<GameObject>> entities;
    Player* playerRef;

    float scrollSpeed;
    float spawnTimer;
    int highScore;
    bool isGameOver;

    sf::Texture coinTex;
    sf::Texture bubbleTex;
    sf::Texture pitTex;
    sf::Texture barrierTex;
    sf::Texture flyingObstacleTex;
    sf::Texture coinTex;
    sf::Texture bubbleTex;

    sf::Font font;
    sf::Text scoreText;
    sf::Text infoText;

    void spawnRandomEntity();
    void loadHighScore();
    void saveHighScore();

    void processEvents();
    void update(float dt);
    void checkCollisions();
    void render();

public:
    Game();
    void restartGame();
    void saveGameState();
    void loadGameState();
    void run();
};