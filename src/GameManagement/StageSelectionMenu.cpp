#include "GameManagement/StageSelectionMenu.h"
#include "GUI/StageMenuGUIManager.h"
#include "GameManagement/Game.h"

using namespace std;


StageSelectionMenu::StageSelectionMenu(sf::RenderWindow *wd) :
    GameState(wd)
{
    guiManager = new StageMenuGUIManager(wd, this, Game::getInstance().getNumUnlockedStages());
}

StageSelectionMenu::~StageSelectionMenu()
{
    delete guiManager;
}

void StageSelectionMenu::update(float deltaTime)
{   
    guiManager->update(deltaTime);
}

void StageSelectionMenu::render()
{   
    window->clear(sf::Color::White);

    guiManager->render(window);

    window->display();
}

void StageSelectionMenu::handleEvents(sf::Event &ev)
{   
    while(window->pollEvent(ev)){

        if (ev.type == sf::Event::Closed){
            window->close();
        }

        guiManager->handleEvent(ev);
    }
}