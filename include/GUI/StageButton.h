#ifndef STAGEBUTTON_H
#define STAGEBUTTON_H

#include "Button.h"

class StageButton : public Button {

public:
    StageButton(float wdPosX, float wdPosY, const std::string& normalTextureFile, const std::string& hoverTextureFile, sf::Font &font, int stage) :
        Button(wdPosX, wdPosY, normalTextureFile, hoverTextureFile) {
            stage_num_txt.setFont(font);
            stage_num_txt.setCharacterSize(50);
            stage_num_txt.setFillColor(sf::Color(253, 226, 148));

            stage_num_txt.setString(to_string(stage));

            bound = stage_num_txt.getLocalBounds();
            stage_num_txt.setOrigin(bound.width / 2.f, bound.height / 2.f);
            
            stage_num_txt.setPosition (
                buttonBounds.left + buttonBounds.width / 2.f,
                buttonBounds.top + 20.f
            );

        }

    void render(sf::RenderWindow *window) override {
        Button::render(window);
        window->draw(stage_num_txt);

        // sf::RectangleShape rect(sf::Vector2f(bound.width, bound.height));
        // rect.setOrigin(bound.width / 2.f, bound.height / 2.f);
        // rect.setPosition(stage_num_txt.getPosition());
        // rect.setFillColor(sf::Color::Transparent);
        // rect.setOutlineColor(sf::Color::Green);
        // rect.setOutlineThickness(2);
        // window->draw(rect);
    }
private:
    sf::Text stage_num_txt;
    sf::FloatRect bound;
};

#endif