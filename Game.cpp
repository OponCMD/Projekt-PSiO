#include "Game.h"
#include "Config.h"
#include "Player.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Game::Game() : window(sf::VideoMode(800, 600), "Endless Runner C++ OOP"),
    scrollSpeed(BASE_SCROLL_SPEED), spawnTimer(0), isGameOver(false) {
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    loadHighScore();

    if (font.loadFromFile("arial.ttf")) {
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(15.f, 15.f);

        infoText.setFont(font);
        infoText.setCharacterSize(40);
        infoText.setFillColor(sf::Color::Red);
        infoText.setPosition(250.f, 250.f);
        infoText.setString("GAME OVER\nNacisnij ENTER");
    }

    restartGame();
}

void Game::loadHighScore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) file >> highScore;
    else highScore = 0;
}

void Game::saveHighScore() {
    std::ofstream file("highscore.txt");
    if (file.is_open()) file << highScore;
}

void Game::restartGame() {
    entities.clear();
    isGameOver = false;
    scrollSpeed = BASE_SCROLL_SPEED;
    spawnTimer = 0.f;

    auto p = std::make_unique<Player>();
    playerRef = p.get();
    entities.push_back(std::move(p));
}

void Game::saveGameState() {
    if (isGameOver) return;
    std::ofstream file("savegame.txt");
    if (file.is_open()) {
        file << playerRef->getScore() << " "
             << playerRef->getPosition().x << " "
             << playerRef->getPosition().y << " "
             << playerRef->getShield() << "\n";
    }
}

void Game::loadGameState() {
    std::ifstream file("savegame.txt");
    if (file.is_open() && !isGameOver) {
        float sc; float px, py; bool shield;
        file >> sc >> px >> py >> shield;
        playerRef->setScore(sc);
        playerRef->setPosition(sf::Vector2f(px, py));
        playerRef->setShield(shield);
    }
}

void Game::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        processEvents();
        if (!isGameOver) {
            update(dt);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            restartGame();
        }
        // OBS£UGA KLAWISZY
        if (!isGameOver && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F5) saveGameState();
            if (event.key.code == sf::Keyboard::F9) loadGameState();
        }
        // PRZEKAZANIE EVENTÓW DO GRACZA
        if (!isGameOver && playerRef) {
            playerRef->handleEvent(event);
        }
    }
}

void Game::update(float dt) {
    playerRef->addScore(dt * 50.f);
    scrollSpeed += 5.f * dt;

    for (auto& entity : entities) {
        entity->update(dt, scrollSpeed);
    }
}

void Game::render() {
    window.clear(sf::Color(50, 150, 200));

    sf::RectangleShape ground(sf::Vector2f(800.f, 100.f));
    ground.setPosition(0, GROUND_Y);
    ground.setFillColor(sf::Color(100, 200, 50));
    window.draw(ground);

    for (auto& entity : entities) {
        entity->draw(window);
    }

    if (font.getInfo().family != "") {
        scoreText.setString("Punkty: " + std::to_string(playerRef->getScore()) + "   Hi-Score: " + std::to_string(highScore));
        window.draw(scoreText);
    }

    if (isGameOver) {
        sf::RectangleShape deathScreen(sf::Vector2f(800.f, 600.f));
        deathScreen.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(deathScreen);
        if (font.getInfo().family != "") window.draw(infoText);
    }

    window.display();
}
