#include "fstream"
#include "GameManagement/StageSelectionMenu.h"
#include "GUI/StageMenuGUIManager.h"

using namespace std;


StageSelectionMenu::StageSelectionMenu(sf::RenderWindow *wd) :
    GameState(wd)
{
    loadSaveData();

    guiManager = new StageMenuGUIManager(wd, this, numUnlockedStages);
    
}

StageSelectionMenu::~StageSelectionMenu()
{
    delete guiManager;
}

void StageSelectionMenu::loadSaveData() 
{
    ifstream fin("../data/save.txt");
    if (!fin) {
        cout << "Cannot load save data\n";
        throw runtime_error("Cannot load save data!\n");
    }

    fin >> this->numUnlockedStages;
    fin.close();
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