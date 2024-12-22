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
#include "GUI/Subject.h"

class Player : public MovingEntity, public Subject {
public:

    Player() = default;

    Player(CharacterType characterType, sf::Vector2f startPos);

    ~Player();


    sf::CircleShape getPickupArea() const;

    float getMaxHP() const;

    float getCurrentHP() const;

    float getCurrentExp() const;
    
    float getMaxExp() const;

    void setArmor(float armor);

    void setBaseDamage(float base_damage);

    void setMoveSpeed(float move_speed);

    void setPosition(sf::Vector2f pos);
    
    void takeDamage(float damage);

    void loseHP(float hp);

    void gainExp(float exp);

    void levelUp();

    virtual void castSkill() = 0;

    void move(sf::Vector2f movement) override;

    void draw(sf::RenderWindow *window);

    void update(float deltaTime);

    void updateMovement(float deltaTime) override;

    void updateAttack(float deltaTime);
    
    bool isKilled();

    void notifyChooseWeapon();

    void notifyPickup();

    EntityType getType() const override {return EntityType::Player;}

private:
    float maxHP;
    float currentHP;
    float maxExp;
    float currentExp;
    float move_speed;
    float damage;
    float armor;
    int exp;
    int level;
    Skill *skill;

    sf::Texture *texture;
    sf::Sprite pSprite;
    Animation animation;

    sf::Vector2f pPosition;
    sf::CircleShape spriteCenter;
    sf::CircleShape pickupArea;

    sf::RectangleShape animation_rect;
    bool faceRight;
    unsigned int row;
    
    bool isVanishing;
    bool isDead;
    bool attackInProgress;
    bool isHurting;

    float totalTime;
    float attackTime;
};

#endif