#include "Enemy/Enemy.h"
#include <math.h>
#include "GUI/Events.h"

Enemy::Enemy(sf::Vector2f pos, float HP, float damage, float move_speed, float strengthMultiplier, bool textureDir) :
    MovingEntity(pos), faceRight(textureDir), textureDirection(textureDir),
    HP(HP), damage(damage), move_speed(move_speed),
    isSpawning(true), isHurting(false), isVanishing(false), isAttacking(false)
{
    this->HP *= strengthMultiplier;
    this->damage *= strengthMultiplier;
    this->move_speed *= strengthMultiplier;
}

void Enemy::move(sf::Vector2f movement)
{
    this->position += movement;
    this->moveBoundingBox(movement);
}

void Enemy::updateMovement(float deltaTime, sf::Vector2f playerPos)
{   
    row = 2;
    sf::Vector2f movement = playerPos - this->position;

    float magnitude = sqrt(movement.x * movement.x + movement.y * movement.y);

    movement /= magnitude;
    movement *= move_speed;

    if (movement.x > 0)
        faceRight = textureDirection;
    else faceRight = !textureDirection;

    this->move(movement);
    this->animation.update(row, deltaTime, faceRight);
}

void Enemy::updateAttack(float deltaTime)
{
    animation.update(row, deltaTime, faceRight);
    //skill->updateAnimation(deltaTime, faceRight);
    if (animation.isFinished(row)){
        //animation.update(row, deltaTime, faceRight);
        attackInProgress = false;
        row = 0;
    }
}

void Enemy::update(float deltaTime, sf::Vector2f playerPos)
{
    if (attackInProgress) {
        this->updateAttack(deltaTime);
    }
    else {
        this->updateMovement(deltaTime, playerPos);
    }

    this->img->getSprite().setTextureRect(animation.uvRect);
}

void Enemy::takeDamage(float damage)
{   
    this->HP -= damage;
    const HPChanged hpChangedEvent(damage, this->position, 0.f, 0.f);
    this->notify(&hpChangedEvent);
}

float Enemy::getDamage()
{
    return damage;
}

float Enemy::getMoveSpeed()
{
    return this->move_speed;
}

float Enemy::getHP()
{
    return this->HP;
}

void Enemy::draw(sf::RenderWindow *window)
{
    this->img->setPosition(this->position);
    this->img->getSprite().setTextureRect(animation.uvRect);
    this->img->draw(window);
    //this->drawBoundingBox(window);
}

bool Enemy::isFacingRight() const
{
    return this->faceRight;
}

bool Enemy::isAlive()
{
    return !this->isVanishing;
}

void Enemy::setFacing(bool faceRight)
{
    this->faceRight = faceRight;
}

void Enemy::setAnimationRow(unsigned row)
{
    this->row = row;
}

bool Enemy::getTextureDirection() const
{
    return textureDirection;
}
float Enemy::getCurHP()
{
    return this->HP;
}

Animation &Enemy::getAnimation()
{
    return this->animation;
}
