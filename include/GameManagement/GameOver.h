#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "GameState.h"

class GameOverGUIManager;

class GameOver : public GameState {
    friend GameOverGUIManager;
public:
    explicit GameOver(sf::RenderWindow *wd);

    ~GameOver();

    void handleEvents(sf::Event &ev) override;

    void update(float deltaTime) override;

    void render() override;

private:

    GameOverGUIManager *guiManager;

};

#endif