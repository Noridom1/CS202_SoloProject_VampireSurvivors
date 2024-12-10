#include "GameManagement/Gameplay.h"
#include <iostream>
#include <random>
#include "Projectile/ProjectileManager.h"
#include "Weapon/WeaponManager.h"
#include "GameManagement/Gameplay.h"

GameplayState::GameplayState(sf::RenderWindow *wd) : 
    GameState(wd), view(sf::FloatRect(0, 0, WIDTH, HEIGHT)), map(new Map("../assets/map/forest/forest.tmx"))
{
    this->startGame(CharacterType::NightBorne);
    BG_texture.loadFromFile("../assets/background.jpg");
    background.setTexture(BG_texture);
    background.setScale(
        window->getSize().x / static_cast<float>(BG_texture.getSize().x),
        window->getSize().y / static_cast<float>(BG_texture.getSize().y)
    );
    background.setOrigin(BG_texture.getSize().x / 2.0f, BG_texture.getSize().y / 2.0f);
}

GameplayState::~GameplayState()
{
    delete this->player;
    delete this->map;
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
    view.setCenter(this->player->getPosition());
    ProjectileManager::getInstance().update(deltaTime);
    ProjectileManager::getInstance().cleanup();
    WeaponManager::getInstance().castWeapons(window, player, deltaTime);
    map->update(window, &view, player->getPosition());
    //view.setCenter(this->player->getPosition());
    //background.setPosition(player->getPosition());
}

void GameplayState::render()
{
    //view.setCenter(window->getSize().x, window->getSize().y);
    this->window->clear(sf::Color(150, 150, 150));

    this->window->setView(view);
    map->draw(window);

    //this->window->draw(background);
    this->player->draw(this->window);
    ProjectileManager::getInstance().draw(this->window);

    //this->window->setView(window->getDefaultView());

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
