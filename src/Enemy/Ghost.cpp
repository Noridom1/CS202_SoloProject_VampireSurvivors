#include "Enemy/Ghost.h"
#include <string>

using namespace std;

float Ghost::maxSpeed = 300.f;
float Ghost::maxHP = 150.f;
float Ghost::maxDamage = 20.f;

Ghost::Ghost(sf::Vector2f pos, float strengthMultiplier) :
    Enemy(
        pos,
        10.f,
        5.f,
        100.f,
        strengthMultiplier
    )
{   
    this->move_speed = min(maxSpeed, move_speed);
    string filename = EnemyPaths.at(EnemyType::Ghost);
    TexturesAnimation textureAnimation = EnemyAnimations.at(EnemyType::Ghost);
    this->img = &EnemyFlyweightFactory::getEnemyImg(EnemyType::Ghost);
    this->animation = Animation(
        &img->getTexture(),
        textureAnimation.numSprites,
        textureAnimation.imageCount,
        textureAnimation.switchTime
    );
    sf::Vector2i animation_size = animation.uvRect.getSize();
    this->img->getSprite().setOrigin(animation_size.x / 2.f, animation_size.y / 2.f);
    this->setBoundingBox();
}

Ghost::~Ghost()
{
    //delete this->img;
}

void Ghost::updateMovement(float deltaTime, sf::Vector2f playerPos)
{
    sf::Vector2f movement = playerPos - this->position;

    float magnitude = sqrt(movement.x * movement.x + movement.y * movement.y);

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

void Ghost::setBoundingBox()
{
    this->boundingBox = sf::FloatRect(0, 0, 20.f, 30.f);
    this->boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    this->boundingBox.top = this->position.y - this->boundingBox.height / 2.f;
}

void Ghost::update(float deltaTime, sf::Vector2f playerPos)
{
    if (isSpawning) {
        row = 0;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isSpawning = false;
        }
    }

    else if (isVanishing) {
        row = 3;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isVanishing = false;
            this->markForDelete();
        }
    }

    else {
        if (isHurting) {
            row = 2;
            animation.update(row, deltaTime, faceRight);
            if(animation.isFinished(row)) {
                row = 1;
                isHurting = false;
            }
        }
        updateMovement(deltaTime, playerPos);
    }
    //this->img->getSprite().setTextureRect(animation.uvRect);
}

void Ghost::takeDamage(float damage)
{
    //cout << "Ghost::takeDamage\n";
    Enemy::takeDamage(damage);
    if (this->HP > 0) {
        isHurting = true;
        row = 2;
    }

    else {
        isVanishing = true;
        row = 3;
    }
}
