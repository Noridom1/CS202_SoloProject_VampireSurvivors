#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameState.h"
#include "Characters.h"

class GameplayState : public GameState {
public:
    GameplayState(sf::RenderWindow *wd) : GameState(wd) {this->startGame(CharacterType::ImeldaBelpaese);}

    void handleEvents(sf::Event &ev) override;
    void update() override;
    void render() override;

    void startGame(CharacterType characterType);
    
private:
    Player player;
    
};

#endif