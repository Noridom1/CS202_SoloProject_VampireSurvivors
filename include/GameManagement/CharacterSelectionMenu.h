#ifndef STAGESELECTION_H
#define STAGESELECTION_H

#include "GameManagement/GameState.h"

class CharacterMenuGUIManager;

class CharacterSelectionMenu : public GameState {
    friend CharacterMenuGUIManager;
public:
    CharacterSelectionMenu(sf::RenderWindow *wd);
    
    ~CharacterSelectionMenu();
    
    void handleEvents(sf::Event &ev) override;

    void update(float deltaTime) override;

    void render() override;

private:
    sf::Text text;
    sf::Font font;

    CharacterMenuGUIManager *guiManager;
    
};

#endif