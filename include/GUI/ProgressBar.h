#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "GUIComponent.h"
#include "Observer.h"
#include "Events.h"

class ProgressBar : public GUIComponent, public Observer {
protected:
    sf::RectangleShape background;  // Background of the bar
    sf::RectangleShape fill;        // Foreground (the actual progress part)
    float progress;                 // Value from 0 to 1 (progress)

public:
    ProgressBar(float wdPosX, float wdPosY, float width, float height)
        : GUIComponent(wdPosX, wdPosY) {
        background.setSize(sf::Vector2f(width, height));
        background.setOutlineColor(sf::Color::Black);
        background.setOutlineThickness(2.f);
        background.setFillColor(sf::Color::Transparent); // Dark gray background

        fill.setSize(sf::Vector2f(0, height));  // Fill will have 0 width initially
        fill.setFillColor(sf::Color(0, 255, 0)); // Green fill for HP bar
    }

    void setProgress(float p) {
        progress = std::clamp(p, 0.f, 1.f);  // Clamp the value between 0 and 1
        fill.setSize(sf::Vector2f(background.getSize().x * progress, background.getSize().y));
    }

    float getProgress() const {
        return progress;
    }

    void render(sf::RenderWindow* window) override {
        window->draw(background);
        window->draw(fill);
    }

    void update(float deltaTime) override {
        // If you want to animate progress or add other updates, do it here
    }

    void handleEvent(const sf::Event &ev) override {

    }

    bool isExpired() const override { return false; }

    bool isFixedWithWindow() const override { return true; }

    void setWorldPosition(sf::RenderWindow *window) override {
        sf::Vector2f worldPos = this->getWorldPosition(window);
        this->background.setPosition(worldPos);
        this->fill.setPosition(worldPos);
    }
};

#endif
