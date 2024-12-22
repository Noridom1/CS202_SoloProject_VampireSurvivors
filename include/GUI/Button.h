#ifndef BUTTON_H
#define BUTTON_H

#include "GUIComponent.h"
#include <functional>
#include "Image.h"

class Button : public GUIComponent {

protected:
    Image* buttonNormal;
    Image* buttonHover;

    sf::FloatRect buttonBounds;
    std::function<void()> onClick;  // Callback function for button click action
    std::function<void()> onHover;

    bool isHovering;

public:
    Button(float wdPosX, float wdPosY, const std::string& normalTextureFile, const std::string& hoverTextureFile) : 
        GUIComponent(wdPosX, wdPosY), isHovering(false)
    {
        buttonNormal = new Image(normalTextureFile);
        buttonHover = new Image(hoverTextureFile);

        this->setPosition(wdPosX, wdPosY);

        buttonBounds = buttonHover->getSprite().getGlobalBounds();

    }

    ~Button() {
        delete buttonNormal;
        delete buttonHover;
    }

    void setOnClick(std::function<void()> action) {
        onClick = action;
    }

    void setOnHover(std::function<void()> action) {
        onHover = action;
    }

    void update(float dt) override {}

    void update(sf::RenderWindow* window) {
        // Check if the mouse is hovering over the button
        if (buttonBounds.contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
            isHovering = true;
            if (onHover) {
                onHover();
            }
        }
        else {
            isHovering = false;
        }
    }

    void handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (isHovering) {
                if (onClick) {
                    onClick();
                }
            }
        }
    }

    virtual void render(sf::RenderWindow* window) override {
        //this->setWorldPosition(window);
        if (isHovering) {
            buttonHover->draw(window);
        }
        else {
            buttonNormal->draw(window);
        }

        drawBoundingBox(window);
    }

    void setPosition(float x, float y) {
        buttonNormal->setPosition(x, y);
        buttonHover->setPosition(x, y);
    }

    void drawBoundingBox(sf::RenderWindow *window) {
        sf::RectangleShape bound(sf::Vector2f(buttonBounds.width, buttonBounds.height));
        bound.setPosition(buttonBounds.left, buttonBounds.top);
        bound.setFillColor(sf::Color::Transparent);
        bound.setOutlineColor(sf::Color::Green);
        bound.setOutlineThickness(1.5f);
        window->draw(bound);
    }

    sf::Vector2f getSize() const {
        return sf::Vector2f(buttonBounds.width, buttonBounds.height);
    }

    void setWorldPosition(sf::RenderWindow* window)  override {
        sf::Vector2f worldPos = this->getWorldPosition(window);
        cout << "world: " << worldPos.x << " " << worldPos.y << endl;
        this->buttonNormal->setPosition(worldPos);
        this->buttonHover->setPosition(worldPos);
        buttonBounds.left = worldPos.x;
        buttonBounds.top = worldPos.y;
    }

    bool isExpired() const override { return false; }


};


#endif