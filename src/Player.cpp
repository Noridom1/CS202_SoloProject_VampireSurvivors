#include "Player.h"
#include <iostream>

Player::Player(CharacterType characterType, sf::Vector2f startPos) :
    MovingEntity(startPos)
{
    const auto& stats = characterStats.at(characterType);
    this->stats = CharacterStats(stats.HP, stats.armor, stats.base_damage, stats.move_speed);
    this->attackInProgress = false;
    this->row = 0;

    const auto& charAnimation = characterAnimations.at(characterType);

    animation = Animation(
        &TextureManagement::getTexture(characterType), 
        charAnimation.numSprites, 
        charAnimation.imageCount, 
        charAnimation.switchTime
    );
    sf::Texture *texture = &TextureManagement::getTexture(characterType);
    sf::Vector2i animation_size = animation.uvRect.getSize();
    cout << "Animation_size: " << animation.uvRect.width << " " << animation.uvRect.height << "\n";
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

    spriteCenter.setRadius(2.0f);
    spriteCenter.setFillColor(sf::Color::Red);
    spriteCenter.setOrigin(spriteCenter.getRadius() / 2.f, spriteCenter.getRadius() / 2.f);
    spriteCenter.setPosition(this->position);
    //spriteCenter.setPosition(bbox.getPosition());
    // bbox.setPosition(pSprite.getPosition().x, pSprite.getPosition().y + 
    //             (animation.uvRect.getSize().y - bbox.getSize().y - 10.0f) / 2.0f );
    //bbox.setPosition(pSprite.getPosition());
    //this->pSprite.setScale(2.0f, 2.0f);s
    
    this->setBoundingBox();

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
    this->stats.base_damage += 10;
    this->stats.move_speed += 0.5;
    this->stats.HP += 20;
}

void Player::takeDamage(float damage)
{
    this->loseHP(damage - this->stats.armor);
}

void Player::loseHP(float hp)
{
    this->stats.HP = 0 ? this->stats.HP - hp < 0: this->stats.HP - hp;
}

void Player::setArmor(int armor)
{
    this->stats.armor = armor;
}

void Player::setBaseDamage(int base_damage)
{
    this->stats.base_damage = base_damage;
}

void Player::setMoveSpeed(float move_speed)
{
    this->stats.move_speed = move_speed;
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

void Player::move(sf::Vector2f movement)
{
    this->position += movement;
    //this->pSprite.move(movement);
    //this->spriteCenter.move(movement);
    //this->animation_rect.move(movement);
    this->moveBoundingBox(movement);

    this->pSprite.setPosition(this->position);
    this->spriteCenter.setPosition(this->position);
    this->animation_rect.setPosition(this->position);
}

void Player::draw(sf::RenderWindow *window)
{   
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
    else { 
        this->updateMovement(deltaTime);
    }

    this->pSprite.setTextureRect(animation.uvRect);
    //std::cout << animation.uvRect.top<< " " << animation.uvRect.left << " " << animation.uvRect.width << " " << animation.uvRect.height << endl;
}

void Player::updateMovement(float deltaTime)
{
    //std::cout << "Updating Idle and Move" << endl;
        sf::Vector2f movement(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= this->stats.move_speed * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x += this->stats.move_speed * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= this->stats.move_speed * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movement.y += this->stats.move_speed * deltaTime;

        if (movement.x == 0 && movement.y == 0)  {
            row = 0;
        }
        else {
            row = 1;
            if (movement.x > 0)
                faceRight = true;
            else if (movement.x < 0)
                faceRight = false;  
        }
        if(movement.x && movement.y) {
            movement /= float(sqrt(2.0));
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

void Player::setBoundingBox()
{
    this->boundingBox = sf::FloatRect(0.f, 0.f, 20.f, 30.f);
    this->boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    this->boundingBox.top = this->position.y  - this->boundingBox.height / 2.f;
}
