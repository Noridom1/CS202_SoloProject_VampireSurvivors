#include <iostream>
#include <random>
#include <sstream>

#include "Player/CharacterFactory.h"
#include "Projectile/ProjectileManager.h"
#include "Enemy/EnemyManager.h"
#include "Weapon/WeaponManager.h"
#include "Pickups/PickupManager.h"

#include "GUI/GameplayGUIManager.h"

#include "GameManagement/Game.h"
#include "GameManagement/Gameplay.h"
#include "GameManagement/MainMenu.h"
#include "GameManagement/GameOver.h"
#include "GameManagement/StageComplete.h"


float Gameplay::mapSize = 0;

Gameplay::Gameplay(sf::RenderWindow *wd, MapName stage) : 
    GameState(wd), view(sf::FloatRect(0, 0, WIDTH, HEIGHT)), guiView(sf::FloatRect(0.f, 0.f, 1280.f, 720.f)),
    map(new Map(stage)), gameEnded(false), isEnding(false),
    collisionHandler(new CollisionHandler(sf::FloatRect(0, 0, map->getWorldSize(), map->getWorldSize()))),
    zoomLevel(750.f), isPausing(false),
    totalTime(0.f)
{
    mapSize = map->getWorldSize();
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

    currentPlayingStage = int(stage) + 1;
    winningTime = 100 + 150 * (int(stage));

    this->startGame(CharacterType::Necromancer);
    cout << "Init gameState\n";
}

Gameplay::~Gameplay()
{
    delete this->player;
    delete this->map;
    delete this->guiManager;
    delete this->damageTextManager;
    delete this->soundManager;
    delete this->collisionHandler;
    cout << "Gameplay::~Gameplay()\n";
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

        guiManager->handleEvent(ev);

        if (isPausing) continue;

        if (ev.type == sf::Event::KeyPressed && !keyPressed) {
            switch (ev.key.code)
            {
                case sf::Keyboard:: Enter:
                    cout << "Pressed Enter\n";
                    WeaponManager::getInstance().addWeapon(WeaponType::KingBible, this->player);
                    break;

                case sf::Keyboard:: Space:
                    cout << "Pressed Space\n";
                    EnemyManager::getInstance().spawnRandomly(EnemyType::Demon, this->player->getPosition());
                    break;

                case sf::Keyboard:: E:
                    ProjectileManager::getInstance().spawnProjectile(ProjectileType::Lightning, player->getPosition(), {0.f, 0.f}, 10.f, 10.f, 10.f);
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
    this->soundManager->updateBackgroundMusic();
    guiManager->update(deltaTime);
    this->window->setView(view);

    if (isPausing) return;

    this->totalTime += deltaTime;
    guiManager->updateTimer(totalTime);
    this->player->update(deltaTime);

    if (player->isKilled()) {
        Game::getInstance().setGameState(std::make_unique<GameOver>(this->window));
        return;
    }

    if (totalTime >= winningTime && !isEnding) {
        isEnding = true;
        EnemyManager::getInstance().onGameWin();
        return;
    }

    if (isEnding && EnemyManager::getInstance().getNumEnemies() == 0) {
        Game::getInstance().setGameState(std::make_unique<StageComplete>(this->window));
        Game::getInstance().updateStages(currentPlayingStage);
    }

    WeaponManager::getInstance().castWeapons(window, player, deltaTime);

    PickupManager::getInstance().update(deltaTime, this->player);
    PickupManager::getInstance().cleanUp();

    EnemyManager::getInstance().update(deltaTime, player->getPosition());
    EnemyManager::getInstance().cleanup();

    ProjectileManager::getInstance().update(deltaTime, player);
    ProjectileManager::getInstance().cleanup();

    
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

    this->window->setView(guiView);
    guiManager->render(window);

    ////this->window->setView(window->getDefaultView());
    this->window->display();
}

void Gameplay::startGame(CharacterType characterType)
{
    EnemyManager::getInstance().reset();
    PickupManager::getInstance().reset();
    WeaponManager::getInstance().reset();
    ProjectileManager::getInstance().reset();

    this->player = CharacterFactory::createPlayer(characterType, map->getCenterPosition());

    guiManager = new GameplayGUIManager(window, this);
    damageTextManager = new DamageTextManager(guiManager);
    soundManager = new SoundManager();

    EnemyManager::getInstance().addDamageTextManager(damageTextManager);
    EnemyManager::getInstance().addSoundManager(soundManager);

    PickupManager::getInstance().addSoundManager(soundManager);
    PickupManager::getInstance().addGUIManager(guiManager);


    cout << "Adding observers to player...\n";
    player->addObserver(this->damageTextManager);
    player->addObserver(this->guiManager->getHPBar());
    player->addObserver(this->guiManager->getExpBar());
    player->addObserver(this->guiManager);
    player->addObserver(this->soundManager);
    cout << "Number of Player observers: " << player->observers.size() << endl;
    //currentState = GameState::GAMEPLAY;
    this->update(0.f);
    this->render();
    player->notifyChooseWeapon();

}

float Gameplay::getMapSize()
{
    return mapSize;
}

void Gameplay::resizeView()
{
    float aspectRatio = float(this->window->getSize().x) / float(this->window->getSize().y);
    view.setSize(WIDTH * aspectRatio, HEIGHT);
}

void Gameplay::pauseGame()
{
    this->isPausing = true;
}

void Gameplay::unpauseGame()
{
    this->isPausing = false;
}
