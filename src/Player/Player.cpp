#include "Player/Player.h"
#include <iostream>
#include "GUI/Events.h"

Player::Player(CharacterType characterType, sf::Vector2f startPos) :
    MovingEntity(startPos),
    isHurting(false), isDead(false), attackInProgress(false), row(0), isVanishing(false),
    level(1)
{
    const auto& stats = characterStats.at(characterType);
    this->currentHP = stats.HP;
    this->maxHP = stats.HP;
    this->maxExp = 100.f;
    this->currentExp = 0.f;
    this->armor = stats.armor;
    this->damage = stats.base_damage;
    this->move_speed = stats.move_speed;

    const auto& charAnimation = characterAnimations.at(characterType);
    sf::Texture *texture = &TextureManagement::getTexture(characterType);
    animation = Animation(
        texture, 
        charAnimation.numSprites, 
        charAnimation.imageCount, 
        charAnimation.switchTime
    );
    sf::Vector2i animation_size = animation.uvRect.getSize();
    //cout << "Animation_size: " << animation.uvRect.width << " " << animation.uvRect.height << "\n";
    sf::Vector2f bbox_size(30.0f, 40.0f);

    this->pSprite.setTexture(*texture);

    this->animation_rect.setFillColor(sf::Color::Transparent);
    this->animation_rect.setSize(sf::Vector2f(static_cast<float>(animation.uvRect.width), static_cast<float>(animation.uvRect.height)));
    this->animation_rect.setOrigin(animation_size.x / 2.f, animation_size.y / 2.f);
    this->animation_rect.setOutlineColor(sf::Color::Red);
    this->animation_rect.setOutlineThickness(1.f);
    this->animation_rect.setPosition(this->position - sf::Vector2f(0, 25.0f));

    pSprite.setOrigin(animation_size.x / 2.0f, animation_size.y / 2.0f);
    pSprite.setPosition(this->position);
    pSprite.setScale(1.2f, 1.2f);

    spriteCenter.setRadius(2.0f);
    spriteCenter.setFillColor(sf::Color::Red);
    spriteCenter.setOrigin(spriteCenter.getRadius() / 2.f, spriteCenter.getRadius() / 2.f);
    spriteCenter.setPosition(this->position);
    //spriteCenter.setPosition(bbox.getPosition());
    // bbox.setPosition(pSprite.getPosition().x, pSprite.getPosition().y + 
    //             (animation.uvRect.getSize().y - bbox.getSize().y - 10.0f) / 2.0f );
    //bbox.setPosition(pSprite.getPosition());
    //this->pSprite.setScale(2.0f, 2.0f);s
    
    pickupArea.setRadius(60.f);
    pickupArea.setFillColor(sf::Color::Transparent);
    pickupArea.setOrigin(pickupArea.getRadius() / 2.f, pickupArea.getRadius() / 2.f);
    pickupArea.setOutlineColor(sf::Color::Red);
    pickupArea.setOutlineThickness(2.f);
    pickupArea.setPosition(this->position);
    
    this->skill = new BladeThunder(sf::Vector2f(250.0f, 100.0f));
    totalTime = 0.0f;
    attackTime = 2.0f;
}

Player::~Player()
{
    delete this->skill;
}

void Player::levelUp()
{
    ++this->level;
    this->damage += 2.f;
    this->move_speed += 5.f;
    this->currentHP += 30.f;
    this->maxHP += 30.f;
    this->maxExp += 50.f;
    this->currentExp = 0.f;
    this->armor += 0.25f;
    this->pickupArea.setRadius(this->pickupArea.getRadius() + 2.f);

    const HPChanged hpChangedEvent(0.f, this->position, this->currentHP, this->maxHP, true);
    const GainExp gainExpEvent(0.f, this->currentExp, this->maxExp);
    const LevelUp levelUpEvent;

    this->notify(&hpChangedEvent);
    this->notify(&gainExpEvent);
    this->notify(&levelUpEvent);
    this->notifyChooseWeapon();
    //cout << "Level " << level;
}

float Player::getMaxHP() const
{
    return maxHP;
}

float Player::getCurrentHP() const
{
    return currentHP;
}

float Player::getCurrentExp() const
{
    return currentExp;
}

float Player::getMaxExp() const
{
    return maxExp;
}

int Player::getLevel() const
{
    return this->level;
}
void Player::takeDamage(float damage)
{
    this->loseHP(max(damage - this->armor, 0.f));
    //cout << "Player taking damage\n";
    if (this->currentHP > 0) {
        row = 3;
        isHurting = true;
        this->animation.reset();
    }
    else {
        row = 4;
        isVanishing = true;
    }

}

void Player::loseHP(float hp)
{  
    this->currentHP = clamp(this->currentHP - hp, 0.f, maxHP);
    const HPChanged hpChangedEvent(hp, this->position, this->currentHP, this->maxHP, true);
    this->notify(&hpChangedEvent);
}

void Player::setArmor(float armor)
{
    this->armor = armor;
}

void Player::setBaseDamage(float base_damage)
{
    this->damage = base_damage;
}

void Player::setMoveSpeed(float move_speed)
{
    this->move_speed = move_speed;
}

void Player::setPosition(sf::Vector2f pos)
{
    this->pSprite.setPosition(pos);
    this->spriteCenter.setPosition(pos);
    this->animation_rect.setPosition(pos);
}

void Player::castSkill()
{
    this->animation.reset();
    this->skill->resetAnimation();
    attackInProgress = true;
    row = 2;
    this->skill->execute(this->pSprite.getPosition());
    //std::cout << "Player position: " << pSprite.getPosition().x << " " << pSprite.getPosition().y << endl;
}

void Player::gainExp(float exp)
{
    this->currentExp += exp;
    const GainExp gainExpEvent(exp, this->currentExp, this->maxExp);
    notify(&gainExpEvent);
    if (this->currentExp >= this->maxExp) 
        levelUp();
}

void Player::move(sf::Vector2f movement)
{
    this->position += movement;
    this->moveBoundingBox(movement);

    this->pSprite.setPosition(this->position);

    this->spriteCenter.setPosition(this->position);
    this->animation_rect.setPosition(this->position);
    this->pickupArea.setPosition(this->position);

}

void Player::draw(sf::RenderWindow *window)
{   
    //window->draw(this->pickupArea);
    window->draw(this->pSprite);
    window->draw(this->spriteCenter);
    //window->draw(this->animation_rect);
    this->drawBoundingBox(window);
    if (attackInProgress){
        this->skill->render(window);
    }
}

void Player::update(float deltaTime)
{
    //totalTime += deltaTime;

    // if (totalTime >= attackTime) {
    //     totalTime -= attackTime;
    //     row = 2;
    //     attackInProgress = true;
    // }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    // {
    //     this->castSkill();
    // }
    
    if (attackInProgress) {
        updateAttack(deltaTime);
    }

    else if (isVanishing) {
        row = 4;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            isDead = true;
        }
    }
    else {
        if (isHurting) {
            row = 3;
            animation.update(row, deltaTime, faceRight);
            if (animation.isFinished(row)) {
                row = 0;
                isHurting = false;
            }
        }
        this->updateMovement(deltaTime);
    }
    this->pSprite.setTextureRect(animation.uvRect);
}

void Player::updateMovement(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= this->move_speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += this->move_speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= this->move_speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += this->move_speed * deltaTime;

    if (movement.x == 0 && movement.y == 0)  {
        row = (row == 1) ? 0 : row;
    }
    else {
        row = (row == 0) ? 1 : row;
        if (movement.x > 0)
            faceRight = true;
        else if (movement.x < 0)
            faceRight = false;  
    }
    if (movement.x && movement.y) {
        movement /= float(sqrt(2.0));
    }
    if(movement.x || movement.y) {
    {
        //cout << "Player::initializing PLayerMoving...\n";
        const PlayerMoving playerMovingEvent;
        //cout << "Player::notifying PLayerMoving...\n";
        this->notify(&playerMovingEvent);
    }
    }
    this->move(movement);
    this->animation.update(row, deltaTime, faceRight);
}

void Player::updateAttack(float deltaTime)
{
    animation.update(row, deltaTime, faceRight);
    skill->updateAnimation(deltaTime, faceRight);
    if (animation.isFinished(row)){
        //animation.update(row, deltaTime, faceRight);
        attackInProgress = false;
        row = 0;
    }
}

sf::CircleShape Player::getPickupArea() const
{
    return this->pickupArea;
}

bool Player::isKilled()
{
    return this->isDead;
}

void Player::notifyChooseWeapon() {
    const StartChooseWeapon startChooseWeaponEvent;
    notify(&startChooseWeaponEvent);
}

void Player::notifyPickup()
{
    const GetPickup getPickupEvent;
    notify(&getPickupEvent);
}

void Player::notifyExplosion(sf::Vector2f position)
{
    sf::Vector2f d = position - this->position;
    float magnitude = sqrt(d.x * d.x + d.y * d.y);
    const Explosion explosionEv(magnitude);
    notify(&explosionEv);
}
