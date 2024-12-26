#include "Enemy/BringerOfDeath.h"
#include "Enemy/BringerOfDeathStates.h"
#include "Enemy/BODSpawningState.h"
#include "Enemy/BODHurtingState.h"
#include "Enemy/BODVanishingState.h"


BringerOfDeath::BringerOfDeath(sf::Vector2f pos, float strengthMultiplier) :
    Enemy(pos, 400.f, 20.f, 150.f, strengthMultiplier),
    maxHP(800.f),
    maxDamage(50.f),
    maxSpeed(200.f),
    attackDist(300.f),
    elapsedTime(0.f),
    atkTime(5.f), castingTime(8.f)
{

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
    this->img->getSprite().setScale(1.5f, 1.5f);
    this->setBoundingBox();
    this->setState(std::make_unique<SpawningState>());
    this->setAnimationRow(0);
}

void BringerOfDeath::setState(std::unique_ptr<BODState> newState)
{
     if (state) {
        state.reset(); // Clean up the previous state
    }
    state = std::move(newState);
}

void BringerOfDeath::update(float deltaTime, sf::Vector2f playerPos)
{
    this->elapsedTime += deltaTime;
    this->updateAnimation(row, deltaTime, this->isFacingRight());
    
    if (this->state) {
        state->update(deltaTime, *this, playerPos);
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
    float width = 50.f;
    float height = 80.f;
    this->boundingBox = sf::FloatRect(
        this->position.x - width / 2.f,
        this->position.y - height / 2.f + 25.f,
        width,
        height  
    );
    stdBBox = this->boundingBox;
}

void BringerOfDeath::setBoundingBoxFace()
{
    float offset_x = 50.f;
    sf::IntRect animationRect = this->getAnimation().uvRect;
    if(this->isFacingRight()) {
        // this->img->getSprite().setOrigin(
        //     animationRect.left + animationRect.width / 2.f + 15.f,
        //     animationRect.height / 2.f
        // );
        boundingBox.left = this->position.x + 25.f;
    }
    else {
        // this->img->getSprite().setOrigin(
        //     animationRect.left + animationRect.width / 2.f - 40.f,
        //     animationRect.height / 2.f
        // );
        boundingBox.left = this->position.x - 60.f;
    }
        
}

void BringerOfDeath::resetElapsedTime()
{
    this->elapsedTime = 0.f;
}

float BringerOfDeath::getElapsedTime()
{
    return elapsedTime;
}

float BringerOfDeath::getAtkTime()
{
    return atkTime;
}

float BringerOfDeath::getCastingTime()
{
    return castingTime;
}

void BringerOfDeath::takeDamage(float damage)
{
    if (isVanishing)
        return;
    Enemy::takeDamage(damage);
    if (this->HP > 0) {
        state->onTakingDamage(*this);
    }
    else {
        this->isVanishing = true;
        this->setAnimationRow(6);
        this->setState(std::make_unique<VanishingState>());
    }
}
