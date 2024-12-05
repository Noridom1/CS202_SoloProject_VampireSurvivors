#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameState.h"
#include "Characters.h"
#include "Projectile/ProjectileManager.h"
#include "Projectile/ProjectileFlyweightFactory.h"

class GameplayState : public GameState {
public:

    GameplayState(sf::RenderWindow *wd) : 
        GameState(wd), view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WIDTH, HEIGHT))
    {
        this->startGame(CharacterType::NightBorne);
    }

    ~GameplayState();
    
    void handleEvents(sf::Event &ev) override;
    void update(float deltaTime) override;
    void render() override;

    void startGame(CharacterType characterType);
    void resizeView();
private:
    Player *player;
    ProjectileManager projectileManager;
    sf::View view;


};



#endif