#ifndef FLOATINGTEXT_H
#define FLOATINGTEXT_H

#include "GUIComponent.h"

class FloatingText : public GUIComponent {
private:
    sf::Text text;             // Text to display
    sf::Vector2f position;     // Current position
    sf::Color color;           // Text color
    float duration;            // Lifespan in seconds
    float elapsedTime;         // Time since creation
    sf::Vector2f velocity;     // Movement speed (e.g., upwards)

public:
    FloatingText(const std::string& value, const sf::Font& font, const sf::Vector2f& startPos, sf::Color color, float duration)
        : position(startPos), color(color), duration(duration), elapsedTime(0), velocity(0, -50), GUIComponent(startPos.x, startPos.y) {
        text.setFont(font);
        text.setString(value);
        text.setCharacterSize(20);
        text.setFillColor(color);
        text.setOutlineThickness(2.f);
        text.setOutlineColor(sf::Color::Black);
        text.setPosition(startPos);
    }

    void update(float dt) override {
        elapsedTime += dt;
        if (elapsedTime < duration) {
            position += velocity * dt; // Move upwards
            color.a = static_cast<sf::Uint8>(255 * (1 - elapsedTime / duration)); // Fade out
            text.setFillColor(color);
            text.setPosition(position);
        }
        else {
            markForDelete();
        }
    }

    void render(sf::RenderWindow* window) override {
        if (elapsedTime < duration) {
            // cout << "Original pos: " << this->position.x << " " << this->position.y << endl;
            // sf::View curView = window->getView();
            // cout << "CurrentView: " << curView.getCenter().x << " " << curView.getCenter().y << endl;
            // cout << "Size: " << curView.getSize().x << " " << curView.getSize().y << endl;
            // sf::Vector2f test(15.f, 15.f);
            // sf::Vector2i screenPosition = window->mapCoordsToPixel(test, window->getView());
            // cout << "ScreenPos: " << screenPosition.x << " " << screenPosition.y << endl;

            //text.setPosition(screenPosition.x, screenPosition.y);
            window->draw(text);
        }
           
    }

    void handleEvent(const sf::Event& event) override {
        // No interaction needed for floating text
    }

    bool isExpired() const override {
        return elapsedTime >= duration;
    }

    void setWorldPosition(sf::RenderWindow *window) {}
};


#endif
