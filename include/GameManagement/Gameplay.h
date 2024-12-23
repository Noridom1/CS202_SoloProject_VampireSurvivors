#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Map/Map.h"
#include "GameState.h"
#include "Player/Player.h"
#include "CollisionHandling/CollisionHandler.h"
#include "GUI/DamageTextManager.h"
#include "Sound/SoundManager.h"

class GameplayGUIManager;

class Gameplay : public GameState {
    friend GameplayGUIManager;
public:

    Gameplay(sf::RenderWindow *wd, MapName stage);

    ~Gameplay();
    
    void handleEvents(sf::Event &ev) override;

    void updateView();

    void updateCollision();

    void update(float deltaTime) override;

    void render() override;

    void startGame(CharacterType characterType);
    
    void resizeView();

    void pauseGame();

    void unpauseGame();

private:
    Player *player;

    sf::Sprite background;
    sf::Texture BG_texture;

    // Camera
    sf::View view;
    float zoomLevel;

    int currentPlayingStage;
    float winningTime;
    bool gameEnded;
    bool isEnding;

    sf::View guiView;

    float totalTime;
    float deltaTime;

    bool isPausing;

    Map *map;

    CollisionHandler* collisionHandler;
    vector<Entity *> nearbyEntities;

    // For debugging:
    sf::Text txt;
    sf::Font font;

    //Game UI
    GameplayGUIManager* guiManager;
    DamageTextManager* damageTextManager;
    SoundManager *soundManager;


};  

#endif