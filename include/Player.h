#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Characters.h"
#include "Texture.h"

class Player : Entity {
public:
    Player() = default;
    Player(CharacterType characterType);


    void levelUp();
    void loseHP(int damage);

    void setArmor(int armor);
    void setBaseDamage(int base_damage);
    void setMoveSpeed(float move_speed);
    void setPosition(sf::Vector2f pos);

    void move(sf::Vector2f new_pos);
    void draw(sf::RenderWindow *window);

private:
    CharacterStats stats;
    int exp;
    int level;

    sf::Sprite pSprite;
    sf::Vector2f pPosition;
        
};

#endif