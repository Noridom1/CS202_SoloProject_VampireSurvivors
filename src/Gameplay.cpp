#include "GameManagement/Gameplay.h"
#include <iostream>
#include <random>

GameplayState::~GameplayState()
{
    delete this->player;
}

void GameplayState::handleEvents(sf::Event &ev)
{  
    bool keyPressed = false;
    while(window->pollEvent(ev)){
        if (ev.type == sf::Event::Closed){
            window->close();
        }
        
        if (ev.type == sf::Event::Resized) {
            cout << "Resizing\n";
            this->resizeView();
        }

        if (ev.type == sf::Event::KeyPressed && !keyPressed) {
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

            case sf::Keyboard:: E:
                cout << "KeyPressed::E\n";
                if (!keyPressed) {
                    this->player->castSkill();
                    keyPressed = true;
                }
                break;  
            
            case sf::Keyboard:: Enter:
                cout << "Pressed Enter\n";
                int lower_x = 0;
                int upper_x = this->window->getSize().x;
                int lower_y = 0;
                int upper_y = this->window->getSize().y;
                std::random_device rd; // Non-deterministic random number generator
                std::mt19937 gen(rd()); // Seed the generator
                std::uniform_int_distribution<> distr_x(lower_x, upper_x);
                int x = distr_x(gen);
                std::uniform_int_distribution<> distr_y(lower_y, upper_y);
                int y = distr_y(gen);
                sf::Vector2f startPos;
                startPos.x = float(x);
                startPos.y = float(y);
                sf::Vector2f pos = this->player->getPosition();
                sf::Vector2f direction(pos - startPos);
                this->projectileManager.spawnProjectile(ProjectileType::Boomerang, startPos, direction, 600.0f);
                break;

            // case sf::Keyboard::Space:
            //     cout << "Pressed Spacebar\n";
            //     Game::getInstance().setGameState(unique_ptr<GameState>(new MenuState(this->window)));
            //     //Game::getInstance().setGameState(make_unique<MenuState>(this->window));
            //     break;
            }
        }

            if (ev.type == sf::Event::KeyReleased) {
                cout << "KeyReleased::E\n";
                if (ev.key.code == sf::Keyboard::E) {
                    keyPressed = false; // Reset when the key is released
                }
            }
    }
}

void GameplayState::update(float deltaTime)
{
    this->player->update(deltaTime);
    this->projectileManager.update(deltaTime);
    projectileManager.cleanup();
}

void GameplayState::render()
{
    view.setCenter(this->player->getPosition());
    this->window->clear(sf::Color(150, 150, 150));
    this->window->setView(view);
    this->player->draw(this->window);
    this->projectileManager.draw(this->window);

    this->window->display();
}

void GameplayState::startGame(CharacterType characterType)
{
    this->player = new Player(characterType);
    //currentState = GameState::GAMEPLAY;
}

void GameplayState::resizeView()
{
    float aspectRatio = float(this->window->getSize().x) / float(this->window->getSize().y);
    view.setSize(WIDTH * aspectRatio, HEIGHT);
}
