#include "GUI/GameplayGUIManager.h"
#include "GameManagement/Gameplay.h"

GameplayGUIManager::GameplayGUIManager(sf::RenderWindow *wd, Gameplay *gameplay) : 
    GUIManager(wd), gameplay(gameplay) 
{
    if (!font.loadFromFile("../assets/fonts/GUIfont.ttf")) {
        cout << "Cannot load Gameplay GUI font\n";
    }
    addComponent(new HPBar(30.f, 30.f, font));
    addComponent(new ExperienceBar(30.f, 100.f, font));

    weaponMenu = new ChooseWeaponMenu(font, gameplay->player);
    weaponMenu->addObserver(this);
}

GameplayGUIManager::~GameplayGUIManager()
{
    delete weaponMenu; 
}

void GameplayGUIManager::showWeaponMenu()
{
    weaponMenu->showMenu();
}

void GameplayGUIManager::hideWeaponMenu()
{
    weaponMenu->hideMenu();
}

void GameplayGUIManager::update(float dt)
{
    GUIManager::update(dt);  // Call base class update
    weaponMenu->update(this->window);
}

void GameplayGUIManager::render(sf::RenderWindow *window)
{
    GUIManager::render(window);  // Call base class render
    weaponMenu->render(window);
}

void GameplayGUIManager::handleEvent(const sf::Event &event)
{
    GUIManager::handleEvent(event);  // Call base class handleEvent
    weaponMenu->handleEvents(event);
}

void GameplayGUIManager::onNotify(const Event *event)
{
    if (event->getEvType() == EventType::StartChooseWeapon) {
        gameplay->pauseGame();
        showWeaponMenu();
    }
    if (event->getEvType() == EventType::FinishChooseWeapon) {
        hideWeaponMenu();
        gameplay->unpauseGame();
    }
}
