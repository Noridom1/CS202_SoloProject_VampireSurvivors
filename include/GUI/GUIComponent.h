#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include <SFML/Graphics.hpp>
#include <iostream>
class GUIComponent {
public:
    GUIComponent(float wdPosX, float wdPosY) : winPosX(wdPosX), winPosY(wdPosY) {}
    virtual void render(sf::RenderWindow* window) = 0;
    virtual void update(float dt) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual bool isExpired() const = 0;
    virtual void setWorldPosition(sf::RenderWindow *window) = 0;
    virtual ~GUIComponent() {}
    virtual sf::Vector2f getWindowPosition() { return {winPosX, winPosY}; }

    sf::Vector2f getWorldPosition(sf::RenderWindow *window) {
        sf::Vector2i windowPos = sf::Vector2i(int(winPosX), int(winPosY));
        return window->mapPixelToCoords(windowPos);
    }

    static sf::Vector2f getWorldPosition(sf::Vector2f pos, sf::RenderWindow *window) {
        sf::Vector2i windowPos = sf::Vector2i(int(pos.x), int(pos.y));
        return window->mapPixelToCoords(windowPos);
    }

protected:
    float winPosX, winPosY;
};

#endif