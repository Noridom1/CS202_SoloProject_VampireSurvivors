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

    int getNumUnlockedCharacters();

    int getSelectedStage();

    int getSelectedCharacter();

    void selectStage(int stage);
    
    void selectCharacter(int character);

    void updateStages(int completedStage);

private:
    Game();

    Game(const Game&) = delete;

    Game& operator=(const Game&) = delete;

    ~Game();
    
    void loadStages();

    void loadCharacters();

    void saveStages();

    void saveCharacters();


private:
    int numUnlockedStages;

    int numUnlockedCharacters;

    int selectedStage;

    int selectedCharacter;

    unique_ptr<GameState> gameState; // current game state

    std::unique_ptr<GameState> nextState;

    sf::RenderWindow *window;

    float deltaTime = 0.0f;

    int maxNumStages = 3;

    int maxNumCharacters = 3;
    
};

#endif
