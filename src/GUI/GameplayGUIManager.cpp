#include "GUI/GameplayGUIManager.h"
#include "GameManagement/Gameplay.h"

GameplayGUIManager::GameplayGUIManager(sf::RenderWindow *wd, Gameplay *gameplay) : 
    GUIManager(wd), gameplay(gameplay) 
{
    if (!font.loadFromFile("../assets/fonts/GUIfont.ttf")) {
        cout << "Cannot load Gameplay GUI font\n";
    }
    hpBar = new HPBar(30.f, 30.f, font);
    expBar = new ExperienceBar(30.f, 100.f, font);

    weaponMenu = new ChooseWeaponMenu(font, gameplay->player);
    weaponMenu->addObserver(this);
}

GameplayGUIManager::~GameplayGUIManager()
{
    delete weaponMenu;
    delete hpBar;
    delete expBar;
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
    hpBar->update(dt);
    expBar->update(dt);
}

void GameplayGUIManager::render(sf::RenderWindow *window)
{
    hpBar->render(window);
    expBar->render(window);
    weaponMenu->render(window);
    window->setView(gameplay->view);
    GUIManager::render(window);  // Call base class render
    window->setView(gameplay->guiView);

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

HPBar* GameplayGUIManager::getHPBar() {
    return this->hpBar;
}

ExperienceBar *GameplayGUIManager::getExpBar()
{
    return this->expBar;
}
