#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Map/Map.h"
#include "GameState.h"
#include "Player/Player.h"
#include "CollisionHandling/CollisionHandler.h"
#include "GUI/DamageTextManager.h"
#include "SoundManager.h"

class Gameplay : public GameState {
    friend class GUIManager;
public:

    Gameplay(sf::RenderWindow *wd);

    ~Gameplay();
    
    void handleEvents(sf::Event &ev) override;

    void updateView();

    void updateCollision();

    void update(float deltaTime) override;

    void render() override;

    void startGame(CharacterType characterType);
    
    void resizeView();
private:
    Player *player;

    sf::Sprite background;
    sf::Texture BG_texture;

    // Camera
    sf::View view;
    float zoomLevel;

    float totalTime;
    float deltaTime;

    Map *map;

    CollisionHandler* collisionHandler;
    vector<Entity *> nearbyEntities;

    // For debugging:
    sf::Text txt;
    sf::Font font;

    //Game UI
    GUIManager* guiManager;
    DamageTextManager* damageTextManager;
    SoundManager *soundManager;
};

#endif