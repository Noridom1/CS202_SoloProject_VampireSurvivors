#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>

class Game {
public:
    // Public method to access the single instance of Game
    static Game& getInstance();

    // Public method to initialize and run the game loop
    void run();

private:
    // Private constructor to prevent direct instantiation
    Game();
    
    // Delete the copy constructor and assignment operator to prevent copying
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Game window and related components
    sf::RenderWindow *window;
    
    // Private method for handling input, updating, and rendering
    void handleEvents();
    void update();
    void render();
};

#endif // GAME_H
