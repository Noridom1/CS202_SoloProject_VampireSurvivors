#ifndef GAMEOVERGUIMANAGER_H
#define GAMEOVERGUIMANAGER_H

#include "GUIManager.h"
#include "Observer.h"
#include "Button.h"

class GameOver;

class GameOverGUIManager : public GUIManager {
private:
    sf::Font font;
    GameOver *menu;

    Image* gameTitle;
    Image* background;

    Button* homeButton;
    Button* newGameButton;

public:
    GameOverGUIManager(sf::RenderWindow *wd, GameOver *menu);

    ~GameOverGUIManager();

    void update(float dt) override;

    void render(sf::RenderWindow* window) override;

    void handleEvent(const sf::Event& event) override;

    void onHomeButtonClicked();

    void onNewGameButtonClicked();
    //void onNotify(const Event *event) override;

};

#endif