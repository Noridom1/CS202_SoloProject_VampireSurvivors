#ifndef PLAYER_H
#define PLAYER_H

#include "Entity/Entity.h"
#include "Characters.h"
#include "Texture.h"
#include "Animation.h"
#include "Skills/Skill.h"
#include "Skills/BladeThunder.h"
#include "Entity/MovingEntity.h"
#include <Map/Map.h>

class Player : public MovingEntity {
public:

    Player() = default;

    Player(CharacterType characterType, sf::Vector2f startPos);

    ~Player();

    void levelUp();

    void takeDamage(float damage);

    void loseHP(float hp);

    void setArmor(int armor);

    void setBaseDamage(int base_damage);

    void setMoveSpeed(float move_speed);

    void setPosition(sf::Vector2f pos);

    void castSkill();

    void move(sf::Vector2f movement) override;

    void draw(sf::RenderWindow *window);

    void update(float deltaTime);

    void updateMovement(float deltaTime) override;

    void updateAttack(float deltaTime);
    
    void setBoundingBox() override;

    EntityType getType() const override {return EntityType::Player;}

private:
    CharacterStats stats;
    int exp;
    int level;
    Skill *skill;

    sf::Texture *texture;
    sf::Sprite pSprite;
    Animation animation;

    sf::Vector2f pPosition;
    sf::CircleShape spriteCenter;

    sf::RectangleShape animation_rect;
    bool faceRight;
    unsigned int row;
    bool attackInProgress;

    float totalTime;
    float attackTime;

        
};

#endif