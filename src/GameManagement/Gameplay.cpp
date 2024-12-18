#include <iostream>
#include <random>
#include "GameManagement/Gameplay.h"
#include "Projectile/ProjectileManager.h"
#include "Weapon/WeaponManager.h"
#include "GameManagement/Gameplay.h"
#include <sstream>

GameplayState::GameplayState(sf::RenderWindow *wd) : 
    GameState(wd), view(sf::FloatRect(0, 0, WIDTH, HEIGHT)), map(new Map("../assets/map/forest/beach.tmx")),
    //quadtree(0, sf::FloatRect(0, 0, map->getWorldSize(), map->getWorldSize()))
    collisionHandler(new CollisionHandler(sf::FloatRect(0, 0, map->getWorldSize(), map->getWorldSize())))
{
    this->startGame(CharacterType::NightBorne);
    BG_texture.loadFromFile("../assets/background.jpg");
    background.setTexture(BG_texture);
    background.setScale(
        window->getSize().x / static_cast<float>(BG_texture.getSize().x),
        window->getSize().y / static_cast<float>(BG_texture.getSize().y)
    );
    background.setOrigin(BG_texture.getSize().x / 2.0f, BG_texture.getSize().y / 2.0f);

    font.loadFromFile("../assets/fonts/Poppins-Bold.ttf");
    this->txt.setFont(font);
    this->txt.setCharacterSize(20);
    this->txt.setFillColor(sf::Color::Red);
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

                case sf::Keyboard:: Space:
                    cout << "Pressed Space\n";
                    EnemyManager::getInstance().spawnRandomly(EnemyType::Ghost, this->player->getPosition());
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
    this->updateView();
    
    ProjectileManager::getInstance().update(deltaTime);
    ProjectileManager::getInstance().cleanup();

    EnemyManager::getInstance().update(deltaTime, player->getPosition());
    EnemyManager::getInstance().cleanup();

    WeaponManager::getInstance().castWeapons(window, player, deltaTime);

    this->updateCollision();
    map->update(window, &view);
    //view.setCenter(this->player->getPosition());
    //background.setPosition(player->getPosition());
}

void GameplayState::updateView()
{
    float mapSize = this->map->getMapSize() * map->getTileSize();
    sf::Vector2f viewSize = view.getSize();

    sf::Vector2f viewCenter = player->getPosition();

    viewCenter.x = max(min(mapSize - viewSize.x / 2.f, viewCenter.x), viewSize.x / 2.f);
    viewCenter.y = max(min(mapSize - viewSize.y / 2.f, viewCenter.y), viewSize.y / 2.f);

    this->view.setCenter(viewCenter);
}

// void GameplayState::updateCollision()
// {
//     static bool isQuadtreeDirty = true;

//     auto objects = this->map->getObjects();

//     vector<Entity*> allEntities;
//     vector<Enemy*> enemies = EnemyManager::getInstance().getEnemies();
//     allEntities.insert(allEntities.end(), objects.begin(), objects.end());
//     //allEntities.insert(allEntities.end(), projectiles.begin(), projectiles.end());
//     allEntities.insert(allEntities.end(), enemies.begin(), enemies.end());
//     allEntities.push_back(this->player);


//     // for (auto obj : allEntities) {
//     //     if (obj->getBoundingBox() == sf::FloatRect(2748.f, 380.f, float(78.5), float(38.5))) {
//     //         cout << "Found == sf::FloatRect(2748.f, 380.f, float(78.5), float(38.5))\n";
//     //     }
//     // }
    
//     if (isQuadtreeDirty) {
//         quadtree.clear();
        
//         for (auto ent : allEntities) {
//             if (ent->getBoundingBox() == sf::FloatRect(2748.f, 380.f, float(78.5), float(38.5))) {
//                 cout << "Found sf::FloatRect(2748.f, 380.f, float(78.5), float(38.5))\n";
//             }
//             quadtree.insert(ent);
//         }

//         isQuadtreeDirty = false;
//     }

//     stringstream ss;
//     ss << "Number of entities: " << allEntities.size() << "\n"
//         << "Number of objects: " << objects.size() << "\n"
//         << "Number of enemies: " << enemies.size() << "\n";

//     //for (auto entity : allEntities) {
//         //vector<Entity *> nearbyEntities;
//         nearbyEntities.clear();
//         quadtree.retrieveNearBy(nearbyEntities, player);
//         quadtree.retrieve(nearbyEntities, player);
//         //cout << "Number of nearby: " << nearbyEntities.size() << endl;
//         ss << "Number of nearby entities: " << nearbyEntities.size() << "\n";
//         for (auto nearbyEntity : nearbyEntities) {
//             if (player->getBoundingBox().intersects(nearbyEntity->getBoundingBox()) && player != nearbyEntity) {
//                 this->collisionHandler->handleCollision(player, nearbyEntity);
//             }
//         }
//     //}

//     txt.setString(ss.str());
//     txt.setPosition(this->view.getCenter() - sf::Vector2f(0.f, this->view.getSize().y / 2.f));


// }
void GameplayState::updateCollision() {
    vector<Enemy*>& enemies = EnemyManager::getInstance().getEnemies();
    vector<StationaryEntity*>& objects = map->getObjects();
    vector<Projectile*>& projectiles = ProjectileManager::getInstance().getProjectiles();

    collisionHandler->handleEnemiesCollision(enemies, objects, projectiles);
    collisionHandler->handlePlayerCollision(player, objects, enemies, projectiles);
}

void GameplayState::render()
{
    //view.setCenter(window->getSize().x, window->getSize().y);
    this->window->clear(sf::Color(150, 150, 150));

    this->window->setView(view);
    map->draw(window);

    //this->window->draw(background);
    this->player->draw(this->window);
    //quadtree.draw(*window);

    window->draw(this->txt);

    for (auto ent : nearbyEntities) {
        ent->drawBoundingBox(window);
    }

    EnemyManager::getInstance().draw(this->window);
    ProjectileManager::getInstance().draw(this->window);

    
    //this->window->setView(window->getDefaultView());

    this->window->display();
}

void GameplayState::startGame(CharacterType characterType)
{
    this->player = new Player(characterType, map->getCenterPosition());
    //currentState = GameState::GAMEPLAY;
}

void GameplayState::resizeView()
{
    float aspectRatio = float(this->window->getSize().x) / float(this->window->getSize().y);
    view.setSize(WIDTH * aspectRatio, HEIGHT);
}
