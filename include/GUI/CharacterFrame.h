#ifndef CHARACTERFRAME_H
#define CHARACTERFRAM_H

#include "Button.h"
#include <unordered_map>
#include "Player/Characters.h"

class CharacterFrame : public Button {

public:
    CharacterFrame(float wdPosX, float wdPosY, const std::string& normalTextureFile, const std::string& hoverTextureFile, sf::Font &font, int character) :
        Button(wdPosX, wdPosY, normalTextureFile, hoverTextureFile) {
            character_name.setFont(font);
            character_name.setCharacterSize(45);
            character_name.setFillColor(sf::Color(253, 226, 148));

            string charName = characterString.at(static_cast<CharacterType>(character));
            character_name.setString(charName);

            sf::FloatRect txt_bound = character_name.getLocalBounds();
            character_name.setOrigin(txt_bound.width / 2.f, txt_bound.height / 2.f);
            
            character_name.setPosition (
                buttonBounds.left + buttonBounds.width / 2.f,
                buttonBounds.top + 80.f
            );

            characterImage = new Image("../assets/GUI/SelectCharacter/" + charName + ".png");
            sf::FloatRect imgBound = characterImage->getSprite().getLocalBounds();
            characterImage->getSprite().setOrigin(imgBound.width / 2.f, imgBound.height / 2.f);

            characterImage->setPosition(
                buttonBounds.left + buttonBounds.width / 2.f,
                buttonBounds.top + 260.f
            );
        }

    ~CharacterFrame() {
        delete characterImage;
    }
    void render(sf::RenderWindow *window) override {
        Button::render(window);
        window->draw(character_name);
        characterImage->draw(window);
    }
private:
    sf::Text character_name;
    Image *characterImage;

    inline static const unordered_map<CharacterType, string> characterString = {
        {CharacterType::Lucy, "LUCY"},
        {CharacterType::Kael, "KAEL"},
        {CharacterType::Astra, "ASTRA"},
    };

      inline static const unordered_map<CharacterType, string> characterImgPath = {
        {CharacterType::Lucy, "../assets/GUI/SelectCharacter/Lucy.png"},
        {CharacterType::Kael, "../assets/GUI/SelectCharacter/Kael.png"},
        {CharacterType::Astra, "../assets/GUI/SelectCharacter/Astra.png"},
    };
};

#endif