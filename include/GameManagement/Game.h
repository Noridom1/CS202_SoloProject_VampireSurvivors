#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.h"
#include "Characters.h"
#include "GameState.h"
#include "Gameplay.h"

using namespace std;

class GameState;

class Game {
public:
    static Game& getInstance();
    void run(); // run the game
    void setGameState(unique_ptr<GameState> newState); // Change between game state
    
private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game();

    
    unique_ptr<GameState> gameState; // current game state


    sf::RenderWindow *window;
    float deltaTime = 0.0f;
};

#endif
