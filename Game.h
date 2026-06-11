#include "Game.h"
#include "Config.h"

Game::Game() : window(sf::VideoMode(800, 600), "Endless Runner C++ OOP") {
    window.setFramerateLimit(60);
}

void Game::run() {
    // Pusta pêtla na razie
}

void Game::processEvents() {}
void Game::render() {}
