#include "GameManagement/Gameplay.h"
#include <iostream>
#include <random>
#include "Projectile/ProjectileManager.h"
#include "Weapon/WeaponManager.h"

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
                case sf::Keyboard:: Enter:
                    cout << "Pressed Enter\n";
                    WeaponManager::getInstance().addWeapon(WeaponType::Boomerang);
                    break;

                case sf::Keyboard:: E:
                    player->castSkill();
                    break;
            // case sf::Keyboard::Space:
            //     cout << "Pressed Spacebar\n";
            //     Game::getInstance().setGameState(unique_ptr<GameState>(new MenuState(this->window)));
            //     //Game::getInstance().setGameState(make_unique<MenuState>(this->window));
            //     break;
            }
        }

            if (ev.type == sf::Event::KeyReleased) {
                keyPressed = false;
            }
    }
}

void GameplayState::update(float deltaTime)
{
    this->player->update(deltaTime);
    ProjectileManager::getInstance().update(deltaTime);
    ProjectileManager::getInstance().cleanup();
    WeaponManager::getInstance().castWeapons(window, player, deltaTime);
}

void GameplayState::render()
{
    view.setCenter(this->player->getPosition());
    this->window->clear(sf::Color(150, 150, 150));
    this->window->draw(background);
    this->window->setView(view);
    this->player->draw(this->window);
    ProjectileManager::getInstance().draw(this->window);

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
