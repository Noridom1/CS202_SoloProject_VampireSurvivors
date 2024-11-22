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
    void run();
    void setGameState(unique_ptr<GameState> newState);
    
private:

    // enum class GameState {
    //     MENU,
    //     GAMEPLAY,
    //     EXIT
    // };

    // Private constructor to prevent direct instantiation
    Game();
    // Delete the copy constructor and assignment operator to prevent copying
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game();

    
    //GameState currentState;
    unique_ptr<GameState> gameState;
    sf::RenderWindow *window;

    Player player;
    
    // Private method for handling input, updating, and rendering
    void handleEvents();
    void update();
    void render();
};

#endif // GAME_H
