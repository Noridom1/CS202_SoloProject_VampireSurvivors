#include "Gameplay.h"
#include <iostream>

void GameplayState::handleEvents(sf::Event &ev)
{
    if (ev.type = sf::Event::KeyPressed) {
        switch (ev.key.code)
        {
        case sf::Keyboard:: W:
            cout << "Pressed W\n";
            break;
        
        case sf::Keyboard:: A:
            cout << "Pressed A\n";
            break;

        case sf::Keyboard:: S:
            cout << "Pressed S\n";
            break;

        case sf::Keyboard:: D:
            cout << "Pressed D\n";
            break;
        
        case sf::Keyboard::Space:
            cout << "Pressed Spacebar\n";
            Game::getInstance().setGameState(unique_ptr<GameState>(new MenuState(this->window)));
            //Game::getInstance().setGameState(make_unique<MenuState>(this->window));

            break;
        }
    }
}

void GameplayState::update()
{

}

void GameplayState::render()
{
    this->window->clear();
    this->player.draw(this->window);
    //std::cout << "This is Gameplay\n";
    this->window->display();
}

void GameplayState::startGame(CharacterType characterType)
{
    this->player = Player(characterType);
    //currentState = GameState::GAMEPLAY;
}
