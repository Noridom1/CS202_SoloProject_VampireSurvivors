#include "GameManagement/MainMenu.h"
#include "GUI/MainMenuGUIManager.h"

using namespace std;

MainMenu::MainMenu(sf::RenderWindow *wd) : GameState(wd)
{
    this->guiManager = new MainMenuGUIManager(wd, this);
}

MainMenu::~MainMenu()
{
    delete this->guiManager;
}

void MainMenu::handleEvents(sf::Event &ev)
{
    while(window->pollEvent(ev)){

        if (ev.type == sf::Event::Closed){
            window->close();
        }

        guiManager->handleEvent(ev);
    }
}

void MainMenu::update(float deltaTime)
{
    guiManager->update(deltaTime);
}

void MainMenu::render()
{
    window->clear(sf::Color::White);

    guiManager->render(window);

    window->display();
}
