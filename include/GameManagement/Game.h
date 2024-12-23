#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Player/Player.h"
#include "Player/Characters.h" 
#include "GameState.h"
#include "GUI/DamageTextManager.h"

using namespace std;

class GameState;

class Game {
public:
    static Game& getInstance();

    void run();
    
    void setGameState(unique_ptr<GameState> newState);

    int getNumUnlockedStages();

    void updateStages(int completedStage);

    
private:
    Game();

    Game(const Game&) = delete;

    Game& operator=(const Game&) = delete;

    ~Game();
    
    void loadStages();

    void saveStages();
private:
    static int numUnlockedStages;

    unique_ptr<GameState> gameState; // current game state

    std::unique_ptr<GameState> nextState;

    sf::RenderWindow *window;

    float deltaTime = 0.0f;

    int maxNumStages = 3;
    
};

#endif
