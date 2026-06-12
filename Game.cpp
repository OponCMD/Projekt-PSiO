#include "Game.h"
#include "Config.h"
#include "Player.h"
#include "Entities.h"
#include "PowerUps.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Wymagane dla std::remove_if

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

void Game::spawnRandomEntity() {
    float startX = 900.f;
    int type = std::rand() % 100;

    if (type < 20) {
        entities.push_back(std::make_unique<Barrier>(startX));
    } else if (type < 40) {
        entities.push_back(std::make_unique<FlyingObstacle>(startX));
    } else if (type < 60) {
        entities.push_back(std::make_unique<Pit>(startX));
        if (std::rand() % 2 == 0) {
            entities.push_back(std::make_unique<Barrier>(startX + 600.f));
        }
    } else if (type < 80) {
        entities.push_back(std::make_unique<ScorePowerUp>(startX, GROUND_Y - 150.f));
    } else {
        entities.push_back(std::make_unique<ShieldPowerUp>(startX, GROUND_Y - 120.f));
    }
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
            checkCollisions();
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
        if (!isGameOver && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F5) saveGameState();
            if (event.key.code == sf::Keyboard::F9) loadGameState();
        }
        if (!isGameOver && playerRef) {
            playerRef->handleEvent(event);
        }
    }
}

void Game::update(float dt) {
    playerRef->addScore(dt * 50.f);
    scrollSpeed += 5.f * dt;

    spawnTimer += dt;
    if (spawnTimer > 1.8f) {
        spawnRandomEntity();
        spawnTimer = 0.f;
    }

    for (auto& entity : entities) {
        entity->update(dt, scrollSpeed);
    }

    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [](const std::unique_ptr<GameObject>& e) { return e->isMarkedForDeletion(); }),
                   entities.end());
}

void Game::checkCollisions() {
    sf::FloatRect playerBounds = playerRef->getBounds();

    for (auto& entity : entities) {
        if (entity.get() == playerRef) continue;

        if (playerBounds.intersects(entity->getBounds())) {
            // Dynamic casting wymóg z listy!
            if (auto powerUp = dynamic_cast<PowerUp*>(entity.get())) {
                if (dynamic_cast<ShieldPowerUp*>(powerUp)) {
                    playerRef->setShield(true);
                } else if (dynamic_cast<ScorePowerUp*>(powerUp)) {
                    playerRef->addScore(500.f);
                }
                powerUp->markForDeletion();
            }
            else if (auto obstacle = dynamic_cast<Obstacle*>(entity.get())) {
                if (auto barrier = dynamic_cast<Barrier*>(obstacle)) {
                    if (playerRef->getIsSmashing()) {
                        barrier->markForDeletion();
                        playerRef->addScore(200.f);
                        continue;
                    }
                }

                if (playerRef->getShield()) {
                    playerRef->setShield(false);
                    obstacle->markForDeletion();
                } else {
                    isGameOver = true;
                    if (playerRef->getScore() > highScore) {
                        highScore = playerRef->getScore();
                        saveHighScore();
                    }
                }
            }
        }
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