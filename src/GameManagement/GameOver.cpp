#include "GameManagement/GameOver.h"
#include "GUI/GameOverGUIManager.h"

using namespace std;

GameOver::GameOver(sf::RenderWindow *wd) : GameState(wd)
{
    this->guiManager = new GameOverGUIManager(wd, this);
}

GameOver::~GameOver()
{
    delete this->guiManager;
}

void GameOver::handleEvents(sf::Event &ev)
{
    while(window->pollEvent(ev)){

        if (ev.type == sf::Event::Closed){
            window->close();
        }

        guiManager->handleEvent(ev);
    }
}

void GameOver::update(float deltaTime)
{
    guiManager->update(deltaTime);
}

void GameOver::render()
{
    window->clear(sf::Color::White);

    guiManager->render(window);

    window->display();
}
