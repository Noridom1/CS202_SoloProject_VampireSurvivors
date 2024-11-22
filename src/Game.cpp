#include "Game.h"
#include <iostream>
#include <filesystem>

Game &Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::run()
{
    while (window->isOpen()) {
        this->handleEvents();
    }
}

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Vampire Survivors");
    this->gameState = make_unique<GameplayState>(this->window);
}

Game::~Game()
{
    delete this->window;
}


void Game::setGameState(unique_ptr<GameState> newState)
{
    this->gameState = move(newState);
}

void Game::handleEvents()
{
    sf::Event ev;
    while (this->window->pollEvent(ev)) {
        // Common events for all game states
        if (ev.type == sf::Event::Closed)
            window->close();
        //cout << typeid(*gameState).name() << endl;
        this->gameState->handleEvents(ev);
        this->gameState->update();
        this->gameState->render();
    }
}


void Game::update()
{
    //Update game entites
   
}

void Game::render()
{
    window->clear();
    //Draw game entities
    window->display();
}
