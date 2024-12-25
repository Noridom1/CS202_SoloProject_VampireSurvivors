#include "Enemy/BringerOfDeath.h"
#include "Enemy/BringerOfDeathStates.h"

BringerOfDeath::BringerOfDeath(sf::Vector2f pos, float timeScale) :
    Enemy(pos, 400.f, 20.f, 150.f),
    maxHP(800.f),
    maxDamage(50.f),
    maxSpeed(200.f),
    attackDist(300.f),
    elapsedTime(0.f)
{
    HP *= (1.f + (timeScale - 1) * 0.5f);
    HP = min(HP, maxHP);

    damage *= (1.f + (timeScale - 1) * 0.1f);
    damage = min(damage, maxDamage);

    move_speed *= (1.f + (timeScale - 1) * 0.1f);
    move_speed = min(move_speed, maxSpeed);

    string filename = EnemyPaths.at(EnemyType::BringerOfDeath);
    TexturesAnimation textureAnimation = EnemyAnimations.at(EnemyType::BringerOfDeath);
    this->img = &EnemyFlyweightFactory::getEnemyImg(EnemyType::BringerOfDeath);

    this->animation = Animation(
        &img->getTexture(),
        textureAnimation.numSprites,
        textureAnimation.imageCount,
        textureAnimation.switchTime
    );

    sf::Vector2i animation_size = animation.uvRect.getSize();
    this->img->getSprite().setOrigin(animation_size.x / 2.f, animation_size.y / 2.f);
    //this->img->getSprite().setScale(0.6f, 0.6f);
    this->setBoundingBox();
}

void BringerOfDeath::setState(std::unique_ptr<BODState> newState)
{
    state = std::move(newState);
}

void BringerOfDeath::update(float deltaTime, sf::Vector2f playerPos)
{
    this->elapsedTime += deltaTime;
    if (isSpawning) {
        row = 0;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            isSpawning = false;
            row = 1;
        }
    }
    
    else if (isVanishing) {
        row = 6;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isVanishing = false;
            this->markForDelete();
        }
    }

    else if (isCharing) {
        row = 2;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isVanishing = false;
            this->markForDelete();
        }
    }

    else {
        //cout << "Demon::Moving\n";
        if (isAttacking) {
            row = 3;
            animation.update(row, deltaTime, faceRight);
            if(animation.isFinished(row)) {
                row = 1;
                isAttacking = false;
                cout << "Finished attack\n";
                this->setBoundingBox();
            }
        }
        updateMovement(deltaTime, playerPos);
        //cout << "Demon::AttackDir: " << attackDir.x << " " << attackDir.y << endl;
        float distance = sqrt(attackDir.x * attackDir.x + attackDir.y * attackDir.y);
        //cout << (totalTime >= attackTime) << endl;
        if (!isAttacking && !isCharing && distance < attackDist) {
            //totalTime = 0.f;
            //isCharging = true;
            row = 2;
        }
    }
}

void BringerOfDeath::updateMovement(float deltaTime, sf::Vector2f playerPos)
{
    
}

void BringerOfDeath::updateAnimation(unsigned row, float deltaTime, bool faceRight)
{
    this->animation.update(row, deltaTime, faceRight);
}

bool BringerOfDeath::isAnimationFinished(unsigned row) const
{
    return this->animation.isFinished(row);
}

void BringerOfDeath::setBoundingBox()
{
    
}
