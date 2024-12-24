#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Entity/Entity.h"
#include "Entity/MovingEntity.h"
#include "Animation.h"
#include <unordered_set>
#include "ProjectileFlyweightFactory.h"
#include "Enemy/Enemy.h"
#include "Player/Player.h"

enum class ProjectileCaster {
    PLayer,
    Enemy,
};

class Projectile : public MovingEntity {
public:
    Projectile(ProjectileType type, sf::Vector2f startPos, sf::Vector2f direction, float speed, float lifetime, float damage);

    void updateAnimation(float deltaTime);

    //virtual void updateMovement(float deltaTime, Map *map) override;

    virtual void update(float deltaTime, Player *player);
    
    void updateMovement(float deltaTime) override {};

    virtual void updateMovement(float deltaTime, Player* player) = 0;

    void draw(sf::RenderWindow* window);

    void move(sf::Vector2f movement) override;

    virtual void markHit();

    bool isMarkedHit();

    float getDamage();

    EntityType getType() const override {return EntityType::Projectile;}

    void updateHitEnemies(Enemy *enemy);

    virtual ProjectileCaster getCaster() = 0;
    
protected:
    sf::Sprite* sprite;
    sf::Vector2f direction;
    Animation animation;
    float move_speed;

    bool markedHit;

    float totalExistedTime;
    float lifeTime;

    float damage;

    unordered_set<Enemy*> hitEnemies;
};


#endif 