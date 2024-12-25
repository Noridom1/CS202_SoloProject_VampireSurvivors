#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include "Entity/Entity.h"
#include "Entity/MovingEntity.h"
#include "Animation.h"
#include "Image.h"
#include "EnemyFlyweightFactory.h"
#include "GUI/Subject.h"

class Enemy : public MovingEntity, public Subject {

public:
    Enemy(sf::Vector2f pos, float HP, float damage, float move_speed, float strengthMultiplier, bool textureDir=false);
    ~Enemy() {}

    void move(sf::Vector2f movement) override;

    void updateMovement(float deltaTime) override {}

    virtual void updateMovement(float deltaTime, sf::Vector2f playerPos);

    void updateAttack(float deltaTime);

    virtual void update(float deltaTime, sf::Vector2f playerPos);

    virtual void takeDamage(float damage);

    float getDamage();
    
    float getMoveSpeed();

    float getHP();
    
    void draw(sf::RenderWindow *window);

    bool isFacingRight() const;
    
    bool isAlive();

    EntityType getType() const override {return EntityType::Enemy;}

    float getCurHP();

    Animation& getAnimation();
    
    virtual EnemyType getEnemyType() const = 0;

protected:
    float HP;
    float move_speed;
    float damage;

    Image *img;
    Animation animation;
    const bool textureDirection;

    bool faceRight;
    unsigned int row;
    bool attackInProgress;

    bool isSpawning;
    bool isAttacking;
    bool isHurting;
    bool isVanishing;

};

#endif