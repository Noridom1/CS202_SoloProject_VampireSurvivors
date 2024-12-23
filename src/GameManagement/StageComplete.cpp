#include "GameManagement/StageComplete.h"
#include "GUI/StageCompleteGUIManager.h"

using namespace std;

StageComplete::StageComplete(sf::RenderWindow *wd) : GameState(wd)
{
    this->guiManager = new StageCompleteGUIManager(wd, this);
}

StageComplete::~StageComplete()
{
    delete this->guiManager;
}

void StageComplete::handleEvents(sf::Event &ev)
{
    while(window->pollEvent(ev)){

        if (ev.type == sf::Event::Closed){
            window->close();
        }

        guiManager->handleEvent(ev);
    }
}

void StageComplete::update(float deltaTime)
{
    guiManager->update(deltaTime);
}

void StageComplete::render()
{
    window->clear(sf::Color::White);

    guiManager->render(window);

    window->display();
}
