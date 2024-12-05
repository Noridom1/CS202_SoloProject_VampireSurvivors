#include "GameManagement/GameState.h"

const float GameState::WIDTH = 1080.0f;
const float GameState::HEIGHT = 720.0f;


void GameState::resizeView(sf::RenderWindow *window, sf::View& view) {
        float aspectRatio = float(window->getSize().x) / float(window->getSize().y);
        view.setSize(WIDTH / aspectRatio, WIDTH);
    }

sf::Vector2i GameState::getMousePosition() const {
        return sf::Mouse::getPosition(*window);
    }
