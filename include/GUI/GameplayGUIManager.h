#ifndef GAMEPLAYGUIMANAGER_H
#define GAMEPLAYGUIMANAGER_H

#include "GUIManager.h"
#include "ChooseWeaponMenu.h"  // Include the header for the weapon menu
#include "Observer.h"

class Gameplay;

class GameplayGUIManager : public GUIManager, public Observer {
private:
    ChooseWeaponMenu* weaponMenu;  // Weapon selection menu specific to gameplay
    sf::Font font;
    Gameplay *gameplay;

public:
    GameplayGUIManager(sf::RenderWindow *wd, Gameplay *gameplay);

    ~GameplayGUIManager();

    void showWeaponMenu();

    void hideWeaponMenu();

    void update(float dt) override;

    void render(sf::RenderWindow* window) override;

    void handleEvent(const sf::Event& event) override;


    HPBar* getHPBar() {
        auto hpBar = getComponentByIndex<HPBar>(0);
        return hpBar;
    }

    
    ExperienceBar* getExpBar() {
        auto expBar = getComponentByIndex<ExperienceBar>(1);
        return expBar;
    }

    void onNotify(const Event *event) override;

};

#endif
