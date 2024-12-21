#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Player/Player.h"
#include "Player/Characters.h" 
#include "GameState.h"
#include "Gameplay.h"
#include "GUI/DamageTextManager.h"

using namespace std;

class GameState;

class Game {
public:
    static Game& getInstance();

    void run();
    
    void setGameState(unique_ptr<GameState> newState);
    
private:
    Game();

    Game(const Game&) = delete;

    Game& operator=(const Game&) = delete;

    ~Game();

    //DamageTextManager& getDamageTextManager() { return damageTextManager; }

private:
    unique_ptr<GameState> gameState; // current game state

    sf::RenderWindow *window;

    float deltaTime = 0.0f;

    // Mangers
    //DamageTextManager damageTextManager;
    //Sound
};

#endif
