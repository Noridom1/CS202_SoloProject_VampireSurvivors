#include "Enemy/Microwave.h"
#include "Projectile/ProjectileFlyweightFactory.h"
#include "Projectile/ProjectileManager.h"

float Microwave::maxSpeed = 200.f;
float Microwave::maxHP = 120.f;
float Microwave::maxDamage = 25.f;

Microwave::Microwave(sf::Vector2f pos, float timeScale) :
    Enemy(
        pos,
        25.f,
        10.f,
        150.f
    ),
    totalTime(0.f), attackTime(8.f)
{
    HP *= (1.f + (timeScale - 1) * 0.4f);
    HP = min(HP, maxHP);

    damage *= (1.f + (timeScale - 1) * 0.1f);
    damage = min(damage, maxDamage);

    move_speed *= (1.f + (timeScale - 1) * 0.1f);
    move_speed = min(move_speed, maxSpeed);
    //this->img = new Image(filename);
    TexturesAnimation textureAnimation = EnemyAnimations.at(EnemyType::Microwave);
    this->img = &EnemyFlyweightFactory::getEnemyImg(EnemyType::Microwave);
    this->animation = Animation(
        &img->getTexture(),
        textureAnimation.numSprites,
        textureAnimation.imageCount,
        textureAnimation.switchTime
    );

    sf::Vector2i animation_size = animation.uvRect.getSize();
    this->img->getSprite().setOrigin(animation_size.x / 2.f, animation_size.y / 2.f);
    this->setBoundingBox();
    //cout << "Init microwave\n";
}

void Microwave::updateMovement(float deltaTime, sf::Vector2f playerPos)
{
    sf::Vector2f movement = playerPos - this->position;

    float magnitude = sqrt(movement.x * movement.x + movement.y * movement.y);
    
    if (magnitude < 100.f) return;

    if (magnitude)
        movement /= magnitude;
    movement *= move_speed * deltaTime;

    if (std::abs(movement.x) > 0.01f) { // Add a small threshold for precision issues
        faceRight = (movement.x > 0) ? textureDirection : !textureDirection;
    }

    if(movement.x && movement.y) {
        movement /= static_cast<float>(sqrt(2));
    }

    this->move(movement);
    this->animation.update(row, deltaTime, faceRight);
}

void Microwave::setBoundingBox()
{
    this->boundingBox = sf::FloatRect(0, 0, 30.f, 20.f);
    this->boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    this->boundingBox.top = this->position.y - this->boundingBox.height / 2.f + 10.f;
}

void Microwave::update(float deltaTime, sf::Vector2f playerPos)
{
    totalTime += deltaTime;
    if (totalTime >= attackTime && !isAttacking) {
        totalTime -= attackTime;
        isAttacking = true;
        row = 2;
        attack(playerPos);
        animation.reset();
        animation.update(row, deltaTime, faceRight);
    }

    if (isSpawning) {
        row = 0;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isSpawning = false;
        }
    }

    else if (isAttacking) {
        row = 2;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            isAttacking = false;
            row = 1;
        }
    }

    else if (isVanishing) {
        //cout << "Microwave::Vanishing\n";
        row = 4;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isVanishing = false;
            this->markForDelete();
        }
    }

    else {
        if (isHurting) {
            //cout << "Hurting animation \n";
            row = 3;
            animation.update(row, deltaTime, faceRight);
            if(animation.isFinished(row)) {
                row = 1;
                isHurting = false;
            }
        }
        updateMovement(deltaTime, playerPos);
    }
}

void Microwave::takeDamage(float damage)
{
    Enemy::takeDamage(damage);
    if (HP > 0) {
        isHurting = true;
        row = 3;
        animation.reset();
        //cout << "Microwave::hurt\n";
    }
    else {
        isVanishing = true;
        row = 4;
    }
}

void Microwave::attack(sf::Vector2f playerPos)
{
    sf::Vector2f direction = playerPos - this->position;
    ProjectileManager::getInstance().spawnProjectile(ProjectileType::ExplodingProjectile, this->position, direction, 75.f, 5.f, this->damage);

}