#ifndef GAMEPLAYGUIMANAGER_H
#define GAMEPLAYGUIMANAGER_H

#include "GUIManager.h"
#include "ChooseWeaponMenu.h"  // Include the header for the weapon menu
#include "Observer.h"

class GameplayGUIManager : public GUIManager, public Observer {
private:
    ChooseWeaponMenu* weaponMenu;  // Weapon selection menu specific to gameplay
    sf::Font font;
    Player *player;

public:
    GameplayGUIManager(sf::RenderWindow *wd, Player *player) : GUIManager(wd), player(player) {
        // Initialize the WeaponMenu here
        if (!font.loadFromFile("../assets/fonts/GUIfont.ttf")) {
            cout << "Cannot load Gameplay GUI font\n";
        }
        addComponent(new HPBar(30.f, 30.f, font));
        addComponent(new ExperienceBar(30.f, 100.f, font));

        weaponMenu = new ChooseWeaponMenu(font, player);
    }

    void showWeaponMenu() {
        weaponMenu->showMenu();
    }

    void hideWeaponMenu() {
        weaponMenu->hideMenu();
    }

    void update(float dt) override {
        GUIManager::update(dt);  // Call base class update
        weaponMenu->update(this->window);
    }

    void render(sf::RenderWindow* window) override {
        GUIManager::render(window);  // Call base class render
        weaponMenu->render(window);
    }

    void handleEvent(const sf::Event& event) override {
        GUIManager::handleEvent(event);  // Call base class handleEvent
        weaponMenu->handleEvents(event);
    }

    ~GameplayGUIManager() {
        delete weaponMenu; 
    }

    HPBar* getHPBar() {
        auto hpBar = getComponentByIndex<HPBar>(0);
        return hpBar;
    }

    
    ExperienceBar* getExpBar() {
        auto expBar = getComponentByIndex<ExperienceBar>(1);
        return expBar;
    }

    void onNotify(const Event *event) override {
        if (event->getEvType() == EventType::PickupChest) {
            showWeaponMenu();
        }
        if (event->getEvType() == EventType::ChoseWeapon) {
            hideWeaponMenu();
        }
    }


};

#endif
