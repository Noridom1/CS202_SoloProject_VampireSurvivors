#ifndef STAGESELECTION_H
#define STAGESELECTION_H

#include "GameManagement/GameState.h"

class StageMenuGUIManager;

class StageSelectionMenu : public GameState {
    friend StageMenuGUIManager;
public:
    StageSelectionMenu(sf::RenderWindow *wd);
    
    ~StageSelectionMenu();
    
    void handleEvents(sf::Event &ev) override;

    void update(float deltaTime) override;

    void render() override;

private:
    sf::Text text;
    sf::Font font;

    StageMenuGUIManager *guiManager;
    
};

#endif