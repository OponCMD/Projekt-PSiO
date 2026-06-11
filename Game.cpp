#include "Game.h"
#include "Config.h"

Game::Game() : window(sf::VideoMode(800, 600), "Endless Runner C++ OOP") {
    window.setFramerateLimit(60);
}

void Game::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }
}

void Game::update(float dt) {
    // Logika wkrótce
}

void Game::render() {
    window.clear(sf::Color(50, 150, 200));

    sf::RectangleShape ground(sf::Vector2f(800.f, 100.f));
    ground.setPosition(0, GROUND_Y);
    ground.setFillColor(sf::Color(100, 200, 50));
    window.draw(ground);

    window.display();
}
