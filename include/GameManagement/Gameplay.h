#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Map/Map.h"
#include "GameState.h"
#include "Characters.h"
#include "Projectile/ProjectileManager.h"
#include "Projectile/ProjectileFlyweightFactory.h"

class GameplayState : public GameState {
public:

    GameplayState(sf::RenderWindow *wd);

    ~GameplayState();
    
    void handleEvents(sf::Event &ev) override;

    void update(float deltaTime) override;

    void render() override;

    void startGame(CharacterType characterType);
    
    void resizeView();
private:
    Player *player;
    //ProjectileManager projectileManager;
    sf::Sprite background;
    sf::Texture BG_texture;
    sf::View view;
    float totalTime;
    float deltaTime;
    Map *map;
};

#endif