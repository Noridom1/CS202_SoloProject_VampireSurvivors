#include "GameManagement/Game.h"
#include <iostream>
#include <filesystem>
#include "GameManagement/Gameplay.h"
#include "GameManagement/MainMenu.h"

Game &Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::run()
{   
    sf::Clock clock;
    while (window->isOpen()) {
        sf::Event ev;
        this->deltaTime = clock.restart().asSeconds();
        
        //this->handleEvents();
        this->gameState->handleEvents(ev);
        this->gameState->update(this->deltaTime);
        this->gameState->render();
        
        if (nextState) {
            this->gameState = move(nextState);
        }
    }
}

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Survive");
    window->setKeyRepeatEnabled(false);
    this->gameState = make_unique<Gameplay>(this->window);
}

Game::~Game()
{
    delete this->window;
}


void Game::setGameState(unique_ptr<GameState> newState)
{
    this->nextState = move(newState);
}

