#include <iostream>
#include <random>
#include <sstream>
#include "GameManagement/Gameplay.h"
#include "Projectile/ProjectileManager.h"
#include "Enemy/EnemyManager.h"
#include "Weapon/WeaponManager.h"
#include "Pickups/PickupManager.h"
#include "GameManagement/Game.h"
#include "GameManagement/Menu.h"
#include "Player/CharacterFactory.h"

Gameplay::Gameplay(sf::RenderWindow *wd) : 
    GameState(wd), view(sf::FloatRect(0, 0, WIDTH, HEIGHT)), map(new Map("../assets/map/snow.tmx")),
    //quadtree(0, sf::FloatRect(0, 0, map->getWorldSize(), map->getWorldSize()))
    collisionHandler(new CollisionHandler(sf::FloatRect(0, 0, map->getWorldSize(), map->getWorldSize()))),
    zoomLevel(800.f)
{
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


    this->startGame(CharacterType::Lucy);
    cout << "Init gameState\n";
}

Gameplay::~Gameplay()
{
    delete this->player;
    delete this->map;
    delete this->guiManager;
    delete this->damageTextManager;
    delete this->soundManager;
}

void Gameplay::handleEvents(sf::Event &ev)
{  
    bool keyPressed = false;
    while(window->pollEvent(ev)){
        if (ev.type == sf::Event::Closed){
            window->close();
        }
        
        if (ev.type == sf::Event::Resized) {
            cout << "Resizing\n";
            //this->resizeView();
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
                    EnemyManager::getInstance().spawnRandomly(EnemyType::Demon, this->player->getPosition());
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

void Gameplay::update(float deltaTime)
{

    this->player->update(deltaTime);

    if (player->isKilled()) {
        Game::getInstance().setGameState(std::make_unique<Menu>(this->window));
        return;
    }

    WeaponManager::getInstance().castWeapons(window, player, deltaTime);

    PickupManager::getInstance().update(deltaTime, this->player);
    PickupManager::getInstance().cleanUp();

    EnemyManager::getInstance().update(deltaTime, player->getPosition());
    EnemyManager::getInstance().cleanup();

    ProjectileManager::getInstance().update(deltaTime, player);
    ProjectileManager::getInstance().cleanup();

    this->soundManager->updateBackgroundMusic();
    
    guiManager->update(deltaTime);
    this->updateCollision();
    this->updateView();
    map->update(window, &view);
    //view.setCenter(this->player->getPosition());
    //background.setPosition(player->getPosition());
}

void Gameplay::updateView()
{
    float mapSize = this->map->getMapSize() * map->getTileSize();

    float aspect = static_cast<float>(window->getSize().x) / static_cast<float>(window->getSize().y);
    sf::Vector2f viewSize;
    if (aspect < 1.0f) {
        viewSize = sf::Vector2f(zoomLevel, zoomLevel / aspect);
    }
    else {
        viewSize = sf::Vector2f(zoomLevel * aspect, zoomLevel);
    }

    if (view.getSize() != viewSize) {
        this->view.setSize(viewSize);
    }

    sf::Vector2f viewCenter = player->getPosition();

    viewCenter.x = max(min(mapSize - viewSize.x / 2.f, viewCenter.x), viewSize.x / 2.f);
    viewCenter.y = max(min(mapSize - viewSize.y / 2.f, viewCenter.y), viewSize.y / 2.f);

    this->view.setCenter(viewCenter);
}

void Gameplay::updateCollision() {
    vector<Enemy*>& enemies = EnemyManager::getInstance().getEnemies();
    vector<StationaryEntity*>& objects = map->getObjects();
    vector<Projectile*>& projectiles = ProjectileManager::getInstance().getProjectiles();

    collisionHandler->handleEnemiesCollision(enemies, objects, projectiles);
    collisionHandler->handlePlayerCollision(player, objects, enemies, projectiles);
}

void Gameplay::render()
{
    this->window->clear();

    this->window->setView(view);
    map->draw(window);
    window->draw(this->txt);

    PickupManager::getInstance().draw(this->window);
    EnemyManager::getInstance().draw(this->window);
    this->player->draw(this->window);
    ProjectileManager::getInstance().draw(this->window);
    guiManager->render(window, this->view);

    ////this->window->setView(window->getDefaultView());
    this->window->display();
}

void Gameplay::startGame(CharacterType characterType)
{
    this->player = CharacterFactory::createPlayer(characterType, map->getCenterPosition());

    guiManager = new GUIManager(State::GAMEPLAY);
    damageTextManager = new DamageTextManager(guiManager);
    soundManager = new SoundManager();

    EnemyManager::getInstance().addDamageTextManager(damageTextManager);
    EnemyManager::getInstance().addSoundManager(soundManager);

    PickupManager::getInstance().addSoundManager(soundManager);

    cout << "Adding observers to player...\n";
    player->addObserver(this->damageTextManager);
    player->addObserver(this->guiManager->getHPBar());
    player->addObserver(this->guiManager->getExpBar());
    player->addObserver(this->soundManager);
    cout << "Number of Player observers: " << player->observers.size() << endl;
    //currentState = GameState::GAMEPLAY;
}

void Gameplay::resizeView()
{
    float aspectRatio = float(this->window->getSize().x) / float(this->window->getSize().y);
    view.setSize(WIDTH * aspectRatio, HEIGHT);
}
