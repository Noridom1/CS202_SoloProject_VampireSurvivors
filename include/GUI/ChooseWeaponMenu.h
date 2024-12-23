#ifndef CHOOSEWEAPONMENU_H
#define CHOOSEWEAPONMENU_H

#include "GUIManager.h"
#include "Button.h"
#include "WeaponIcon.h"
#include <vector>
#include "Weapon/WeaponManager.h"
#include "Player/Player.h"

class ChooseWeaponMenu : public Subject {

private:
    bool isVisible;  // Flag to show or hide the menu
    Image* background;
    sf::Vector2f backgroundPos;

    vector<Button*> buttons;
    vector<WeaponIcon*> weaponIcons;
    Player *player;
    sf::Font font;

public:
    ChooseWeaponMenu(sf::Font &font, Player *player) : isVisible(false), font(font), player(player) {

        this->background = new Image("../assets/GUI/GamePlaying/ChooseWeapon_BG.png");

        backgroundPos = sf::Vector2f(320.f, 50.f);

        this->background->setPosition(backgroundPos);

        buttons.emplace_back(new Button(740.f, 200.f, "../assets/GUI/GamePlaying/ChooseButton_Normal.png", "../assets/GUI/GamePlaying/ChooseButton_Hover.png"));
        buttons.emplace_back(new Button(740.f, 360.f, "../assets/GUI/GamePlaying/ChooseButton_Normal.png", "../assets/GUI/GamePlaying/ChooseButton_Hover.png"));
        buttons.emplace_back(new Button(740.f, 520.f, "../assets/GUI/GamePlaying/ChooseButton_Normal.png", "../assets/GUI/GamePlaying/ChooseButton_Hover.png"));

    }

    ~ChooseWeaponMenu() {
        delete this->background;

        for (auto& button : buttons) {
            delete button;
        }

        for (auto wi : weaponIcons) {
            delete wi;
        }
    }

    void render(sf::RenderWindow* window) {
        if (isVisible) {
            this->background->draw(window);

            for (auto& button : buttons) {
                button->render(window);
            }

            for (auto wi : weaponIcons) {
                wi->render(window);
            }
        }
    }

    bool isMenuVisible() const {
        return isVisible;
    }

    void showMenu() {
        isVisible = true;
        cout << "Show Choosing Weapon Menu...\n";
        vector<WeaponType> weapons = WeaponManager::getInstance().randomWeapons();
        cout << "ChooseWeaponMenu::showMenu(): randomed weapons\n";
        update(weapons);
    }

    void hideMenu() {
        isVisible = false;
        
    }

    void handleEvents(const sf::Event& event) {
        if (isVisible) {
            for (auto& button : buttons) {
                button->handleEvent(event);
            }
        }
    }

    void update(vector<WeaponType> weaponsTypes) {
        if(weaponsTypes.size() != 3) return;

        for (auto icon : weaponIcons) {
            delete icon;
        }

        weaponIcons.clear();
        float posX = 460.f;
        float posY = 190.f;
        for (int i = 0; i < weaponsTypes.size(); ++i) {
            WeaponType wp = weaponsTypes[i];
            WeaponIcon *newIcon = new WeaponIcon(wp, posX, posY, font, WeaponManager::getInstance().getLevelByType(wp));
            this->weaponIcons.emplace_back(newIcon);
            this->buttons[i]->setOnClick([wp, this]() {
                WeaponManager::getInstance().addWeapon(wp, this->player);
                const FinishChooseWeapon ev;
                this->notify(&ev);
                hideMenu();
            });
            posY += 160.f;
        }
        cout << "ChooseWeaponMenu::update(): update weapons icons\n";
    }

    void update(sf::RenderWindow *window) {
        for (auto button : buttons) {
            button->update(window);
        }
        
    }
    
};

#endif
