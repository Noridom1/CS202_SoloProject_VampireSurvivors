#include "GameManagement/CharacterSelectionMenu.h"
#include "GUI/CharacterMenuGUIManager.h"
#include "GameManagement/Game.h"
using namespace std;


CharacterSelectionMenu::CharacterSelectionMenu(sf::RenderWindow *wd) :
    GameState(wd)
{
    guiManager = new CharacterMenuGUIManager(wd, this, Game::getInstance().getNumUnlockedCharacters());
}

CharacterSelectionMenu::~CharacterSelectionMenu()
{
    delete guiManager;
}

void CharacterSelectionMenu::update(float deltaTime)
{   
    guiManager->update(deltaTime);
}

void CharacterSelectionMenu::render()
{   
    window->clear(sf::Color::White);

    guiManager->render(window);

    window->display();
}

void CharacterSelectionMenu::handleEvents(sf::Event &ev)
{   
    while(window->pollEvent(ev)){

        if (ev.type == sf::Event::Closed){
            window->close();
        }

        guiManager->handleEvent(ev);
    }
}