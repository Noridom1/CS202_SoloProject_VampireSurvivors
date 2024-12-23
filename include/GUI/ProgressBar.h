#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>
#include "GUIComponent.h"
#include "Observer.h"
#include "Events.h"
#include "Image.h"

class ProgressBar : public GUIComponent, public Observer {
protected:
    // sf::RectangleShape background;  // Background of the bar
    // sf::RectangleShape fill;        // Foreground (the actual progress part)
    // float progress;                 // Value from 0 to 1 (progress)

    Image* background;
    Image* fill;
    sf::Text progressText;
    float progress;
    sf::Vector2f offset;

public:
    ProgressBar(float wdPosX, float wdPosY, sf::Font &font)
        : GUIComponent(wdPosX, wdPosY), offset(0.f, 0.f) {
        background = new Image("../assets/GUI/GamePlaying/ProgressBar_BG.png");
        background->setPosition(sf::Vector2f(wdPosX, wdPosY));
        this->progressText.setFillColor(sf::Color::White);
        this->progressText.setFont(font);
        this->progressText.setCharacterSize(20);
    }

    ~ProgressBar() {
        delete background;
    }

    void setProgress(float p) {
        progress = std::clamp(p, 0.f, 1.f);
        if (fill) {
            fill->getSprite().setScale(progress, 1.f);
        }
    }

    float getProgress() const {
        return progress;
    }

    void render(sf::RenderWindow* window) override {
        this->setWorldPosition(window);
        background->draw(window);
        fill->draw(window);
        window->draw(progressText);
    }

    void update(float deltaTime) override {
        // If you want to animate progress or add other updates, do it here
        string txt = to_string(int(progress * 100)) + "%";
        this->progressText.setString(txt);
    }

    void handleEvent(const sf::Event &ev) override {

    }

    bool isExpired() const override { return false; }

    void setWorldPosition(sf::RenderWindow *window) override {
        sf::Vector2f worldPos = this->getWorldPosition(window);
        this->background->setPosition(worldPos);
        this->fill->setPosition(worldPos + offset);

        sf::FloatRect backgroundRect = background->getSprite().getLocalBounds();
        this->progressText.setOrigin(
            this->progressText.getLocalBounds().width / 2.f,
            this->progressText.getLocalBounds().height / 2.f
        );
        this->progressText.setPosition(
            worldPos + 
            sf::Vector2f(backgroundRect.width / 2.f, backgroundRect.height / 2.f) +
            sf::Vector2f(0.f, -10.f)
            );
    }
};

#endif
