#include "GameManagement/GameState.h"

const float GameState::WIDTH = 1080.0f;
const float GameState::HEIGHT = 720.0f;

void GameState::resizeView(sf::RenderWindow& window, sf::View& view, const sf::Event::SizeEvent& sizeEvent) {
    float newAspectRatio = static_cast<float>(sizeEvent.width) / sizeEvent.height;

    sf::Vector2f viewSize = view.getSize();

    if (newAspectRatio > 1.0f) {
        view.setSize(viewSize.y * newAspectRatio, viewSize.y);
    } else {
        view.setSize(viewSize.x, viewSize.x / newAspectRatio);
    }

    // Set the view back to the window
    window.setView(view);
}
sf::Vector2i GameState::getMousePosition() const {
        return sf::Mouse::getPosition(*window);
    }
