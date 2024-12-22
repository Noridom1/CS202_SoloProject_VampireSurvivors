#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MainMenuGUIManager;

class MainMenu : public GameState {
    friend MainMenuGUIManager;
public:
    explicit MainMenu(sf::RenderWindow *wd);

    ~MainMenu();

    void handleEvents(sf::Event &ev) override;

    void update(float deltaTime) override;

    void render() override;

private:

    MainMenuGUIManager *guiManager;

};

#endif