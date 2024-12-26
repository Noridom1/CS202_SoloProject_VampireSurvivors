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
    timer = new Timer(1110.f, 30.f, font);

    lvBG = new Image("../assets/GUI/GamePlaying/lvBG.png");
    lvBG->setPosition(30.f, 170.f);

    level.setString("Level: 1");
    level.setFont(font);
    level.setCharacterSize(25);
    level.setPosition(44.f, 183.f);
    level.setFillColor(sf::Color(253, 226, 148));

    weaponMenu = new ChooseWeaponMenu(font, gameplay->player);
    weaponMenu->addObserver(this);

}

GameplayGUIManager::~GameplayGUIManager()
{
    delete weaponMenu;
    delete hpBar;
    delete expBar;
    delete timer;
    delete lvBG;
}

void GameplayGUIManager::showWeaponMenu()
{
    weaponMenu->showMenu();
}

void GameplayGUIManager::hideWeaponMenu()
{
    weaponMenu->hideMenu();
}

void GameplayGUIManager::updateTimer(float time)
{
    timer->update(time);
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
    lvBG->draw(window);
    window->draw(level);

    weaponMenu->render(window);
    timer->render(window);

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
    if (event->getEvType() == EventType::LevelUp) {
        this->level.setString("Level: " + to_string(gameplay->player->getLevel()));
    }
}

HPBar* GameplayGUIManager::getHPBar() {
    return this->hpBar;
}

ExperienceBar *GameplayGUIManager::getExpBar()
{
    return this->expBar;
}
