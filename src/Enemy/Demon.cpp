#include "Enemy/Demon.h"

float Demon::maxSpeed = 300.f;
float Demon::maxHP = 500.f;
float Demon::maxDamage = 80.f;
float Demon::attackDist = 300.f;
float Demon::duration = 1.2f;

Demon::Demon(sf::Vector2f pos, float timeScale) :
    Enemy(
        pos,
        100.f,
        20.f,
        200.f
    ), 
    isSpawning(true), isHurting(false), isVanishing(false), isAttacking(false), isCharging(false),
    effectArea(pos.x - 70.f, pos.y + 20.f, 50.f, 40.f),
    attackTime(2.5f), totalTime(0.f), attackingTime(0.f)
{
    HP *= (1.f + (timeScale - 1) * 0.5f);
    HP = min(HP, maxHP);

    damage *= (1.f + (timeScale - 1) * 0.1f);
    damage = min(damage, maxDamage);

    move_speed *= (1.f + (timeScale - 1) * 0.1f);
    move_speed = min(move_speed, maxSpeed);

    string filename = EnemyPaths.at(EnemyType::Demon);
    TexturesAnimation textureAnimation = EnemyAnimations.at(EnemyType::Demon);
    this->img = &EnemyFlyweightFactory::getEnemyImg(EnemyType::Demon);

    this->animation = Animation(
        &img->getTexture(),
        textureAnimation.numSprites,
        textureAnimation.imageCount,
        textureAnimation.switchTime
    );

    sf::Vector2i animation_size = animation.uvRect.getSize();
    this->img->getSprite().setOrigin(animation_size.x / 2.f, animation_size.y / 2.f);
    this->img->getSprite().setScale(0.6f, 0.6f);
    this->setBoundingBox();

}

Demon::~Demon()
{
    //delete img;
}

void Demon::updateMovement(float deltaTime, sf::Vector2f playerPos)
{
    sf::Vector2f movement;
    float magnitude;
    if (isAttacking) {
        movement = attackDir;
    }
    else {
        movement = playerPos - this->position;
        attackDir = movement;
    }

    magnitude = sqrt(movement.x * movement.x + movement.y * movement.y);
    
    if (magnitude)
        movement /= magnitude;


    movement *= (move_speed + (isAttacking) * 300.f) * deltaTime;

    if (std::abs(movement.x) > 0.01f && !isAttacking) { // Add a small threshold for precision issues
        faceRight = (movement.x > 0) ? textureDirection : !textureDirection;
    }

    if(movement.x && movement.y) {
        movement /= static_cast<float>(sqrt(2));
    }

    this->move(movement);
    this->animation.update(row, deltaTime, faceRight);
}

void Demon::setBoundingBox()
{
    this->boundingBox = sf::FloatRect(0, 0, 40.f, 50.f);
    this->boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    this->boundingBox.top = this->position.y - this->boundingBox.height / 2.f;
    this->normalBoundingBox = boundingBox;
}

void Demon::update(float deltaTime, sf::Vector2f playerPos)
{
    totalTime += deltaTime;
    if (isSpawning) {
        //cout << "Demon::Spawning\n";
        row = 0;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            isSpawning = false;
            row = 1;
        }
    }

    else if (isVanishing) {
        //cout << "Demon::Vanishing\n";
        row = 4;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isVanishing = false;
            this->markForDelete();
        }
    }

    else if (isCharging) {
        //cout << "Demon::Charging\n";
        row = 2;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 3;
            isAttacking = true;
            isCharging = false;
            //faceAttack = faceRight;
            this->attackDir = playerPos - this->position;
            animation.reset();
            setEffectiveArea();
            //cout << "Called attack\n";
        }
    }

    else {
        //cout << "Demon::Moving\n";
        if (isAttacking) {
            attackingTime += deltaTime;
            row = 3;
            animation.update(row, deltaTime, faceRight);
            if(/*animation.isFinished(row)*/ attackingTime >= duration ) {
                row = 1;
                isAttacking = false;
                attackingTime = 0.f;
                totalTime = 0.f;
                cout << "Finished attack\n";
                resetBoundingbox();
            }
        }
        updateMovement(deltaTime, playerPos);
        //cout << "Demon::AttackDir: " << attackDir.x << " " << attackDir.y << endl;
        float distance = sqrt(attackDir.x * attackDir.x + attackDir.y * attackDir.y);
        //cout << (totalTime >= attackTime) << endl;
        if (!isAttacking && !isCharging && distance < attackDist && totalTime >= attackTime) {
            totalTime = 0.f;
            isCharging = true;
            row = 2;
        }
    }
    //this->img->getSprite().setTextureRect(animation.uvRect);
}

void Demon::takeDamage(float damage)
{
    Enemy::takeDamage(damage);
    //cout << "Demon::takeDamage " << damage << endl;

    if (HP > 0) {
        isHurting = true;
    }
    else {
        isVanishing = true;
        row = 4;
    }
}

void Demon::setEffectiveArea()
{
    this->normalBoundingBox = boundingBox;
    this->boundingBox.width *= 2.f;
    this->boundingBox.top += boundingBox.height / 2.f;
    this->boundingBox.height *= 0.75f;

    if (!faceRight) {
        this->boundingBox.left += boundingBox.width / 6.f;
        cout << "Set effectiveArea facing right\n";

    }
    else {
        this->boundingBox.left -= boundingBox.width / 2.f;
        cout << "Set effectiveArea facing left\n";

    }

}

void Demon::resetBoundingbox()
{
    this->setBoundingBox();
}
