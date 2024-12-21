#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include <SFML/Graphics.hpp>

class GUIComponent {
public:
    GUIComponent(float wdPosX, float wdPosY) : wdPosX(wdPosX), wdPosY(wdPosY) {}
    virtual void render(sf::RenderWindow* window) = 0;
    virtual void update(float dt) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual bool isExpired() const = 0;
    virtual ~GUIComponent() {}
    virtual sf::Vector2f getWindowPosition() { return {wdPosX, wdPosY}; }
    virtual bool isFixedWithWindow() const = 0;

    sf::Vector2f getWorldPosition(sf::RenderWindow *window) {
        sf::Vector2i windowPos = sf::Vector2i(int(wdPosX), int(wdPosY));
        return window->mapPixelToCoords(windowPos);
    }

    virtual void setWorldPosition(sf::RenderWindow *window) = 0;

protected:
    float wdPosX, wdPosY;
};

#endif