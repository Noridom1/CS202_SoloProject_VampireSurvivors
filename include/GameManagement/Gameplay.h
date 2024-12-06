#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameState.h"
#include "Characters.h"
#include "Projectile/ProjectileManager.h"
#include "Projectile/ProjectileFlyweightFactory.h"

class GameplayState : public GameState {
public:

    GameplayState(sf::RenderWindow *wd) : 
        GameState(wd), view(sf::FloatRect(0, 0, WIDTH, HEIGHT))
    {
        this->startGame(CharacterType::NightBorne);
        BG_texture.loadFromFile("../assets/background.jpg");
        background.setTexture(BG_texture);
        background.setScale(
            window->getSize().x / static_cast<float>(BG_texture.getSize().x),
            window->getSize().y / static_cast<float>(BG_texture.getSize().y)
        );
    }

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
};



#endif