#include "Game.h"

Game &Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::run()
{
   while(window->isOpen()) {
        this->handleEvents();
        this->update();
        this->render();
   }
}

Game::Game() : window(new sf::RenderWindow(sf::VideoMode(1080, 720), "Vampire Survivors")) 
{
    
}

void Game::handleEvents()
{
    sf::Event ev;
    while (this->window->pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            window->close();
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
