#ifndef WEAPONICON_H
#define WEAPONICON_H

#include "GUIComponent.h"
#include "Image.h"
#include <unordered_map>
#include "Weapon/Weapon.h"


const unordered_map<WeaponType, string> WeaponIconPaths = {
    {WeaponType::Boomerang, "../assets/textures/projectiles/boomerang_icon.png"},
    {WeaponType::KingBible, "../assets/textures/projectiles/KingBible_icon.png"},

};

const unordered_map<WeaponType, string> WeaponDescription = {
    {WeaponType::Boomerang, "Boom boom Boomerang!"},
    {WeaponType::KingBible, "../assets/textures/projectiles/KingBible_icon.png"},

};

class WeaponIcon : GUIComponent {

public:
    WeaponIcon(WeaponType type, float wdPosX, float wdPosY, sf::Font &font, int level) : GUIComponent(wdPosX, wdPosY) {

        this->background = new Image("../assets/GUI/GamePlaying/WeaponIcon_BG.png");
        this->icon = new Image(WeaponIconPaths.at(type));

        this->level.setFont(font);
        this->level.setFillColor(sf::Color(253, 226, 148));
        this->level.setCharacterSize(15);
        if (level != 0)
            this->level.setString("LV." + to_string(level));
        else 
            this->level.setString("NEW!");

        this->iconOffset = sf::Vector2f(15.f, 7.f);
        this->levelOffset = sf::Vector2f(27.f, 75.f);

        this->setPosition(wdPosX, wdPosY);
    }

    ~WeaponIcon() {
        delete this->background;
        delete this->icon;
    }

    void render(sf::RenderWindow* window) override {
        this->background->draw(window);
        this->icon->draw(window);
        window->draw(level);
    }


    void updateLevel(int level) {
        this->level.setString("LV." + to_string(level));
    }

    void setWorldPosition(sf::RenderWindow *window) {
        sf::Vector2f worldPos = this->getWorldPosition(window);
        this->background->setPosition(worldPos);
        this->icon->setPosition(worldPos + iconOffset);
        this->level.setPosition(worldPos + levelOffset);
    }

    void setPosition(float x, float y) {
        sf::Vector2f position(x, y);
        this->background->setPosition(position);
        this->icon->setPosition(position + iconOffset);
        this->level.setPosition(position + levelOffset);
    }

    void update(float dt) override {}

    void handleEvent(const sf::Event& event) override {

    }

    bool isExpired() const override {
        return false;
    }

private:
    Image* background;
    Image* icon;
    sf::Text weaponName;
    sf::Text level;

    sf::Vector2f iconOffset;
    sf::Vector2f levelOffset;

};

#endif