#ifndef BUTTON_H
#define BUTTON_H

#include "GUIComponent.h"
#include <functional>
#include "Image.h"

class Button : public GUIComponent {
private:
    Image* buttonNormal;
    Image* buttonHover;

    sf::FloatRect buttonBounds;
    std::function<void()> onClick;  // Callback function for button click action

    bool isHovering;

public:
    Button(float wdPosX, float wdPosY, const std::string& normalTextureFile, const std::string& hoverTextureFile) : 
        GUIComponent(wdPosX, wdPosY), isHovering(false)
    {
        buttonNormal = new Image(normalTextureFile);
        buttonHover = new Image(hoverTextureFile);

        buttonBounds = buttonHover->getSprite().getLocalBounds();
    }

    ~Button() {
        delete buttonNormal;
        delete buttonHover;
    }

    // Set the callback function for button click
    void setOnClick(std::function<void()> action) {
        onClick = action;
    }

    // Update the button state based on mouse position
    void update(float dt) override {}

    void update(sf::RenderWindow* window) {
        // Check if the mouse is hovering over the button
        this->setWorldPosition(window);
        if (buttonBounds.contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
            isHovering = true;
        }
        else {
            isHovering = false;
        }
    }

    // Handle mouse events
    void handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (isHovering) {
                if (onClick) {
                    onClick();  // Trigger the click action
                }
            }
        }
    }

    // Render the button on the screen
    void render(sf::RenderWindow* window) override {
        if (isHovering) {
            buttonHover->draw(window);
        }
        else {
            buttonNormal->draw(window);
        }

        sf::RectangleShape bound(sf::Vector2f(buttonBounds.width, buttonBounds.height));
        bound.setPosition(buttonBounds.left, buttonBounds.top);
        bound.setFillColor(sf::Color::Transparent);
        bound.setOutlineColor(sf::Color::Green);
        bound.setOutlineThickness(1.5f);
        window->draw(bound);

    }

    void setPosition(float x, float y) {
        buttonHover->setPosition(x, y);
    }

    sf::Vector2f getSize() const {
        return sf::Vector2f(buttonBounds.width, buttonBounds.height);
    }

    void setWorldPosition(sf::RenderWindow* window)  override {
        sf::Vector2f worldPos = this->getWorldPosition(window);
        this->buttonNormal->setPosition(worldPos);
        this->buttonHover->setPosition(worldPos);
        buttonBounds.left = worldPos.x;
        buttonBounds.top = worldPos.y;
    }

    bool isExpired() const override { return false; }
    bool isFixedWithWindow() const override { return true; }


};


#endif