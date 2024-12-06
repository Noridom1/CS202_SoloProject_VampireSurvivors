#include "Player.h"
#include <iostream>

Player::Player(CharacterType characterType) //: 
    //animation(&TextureManagement::getTexture(characterType), )
{
    const auto& stats = characterStats.at(characterType);
    this->stats = CharacterStats(stats.HP, stats.armor, stats.base_damage, stats.move_speed);
    this->attackInProgress = false;
    this->row = 0;
    this->currentState = AnimationState::Idle;

    const auto& charAnimation = characterAnimations.at(characterType);

    animation = Animation(
        &TextureManagement::getTexture(characterType), 
        charAnimation.numSprites, 
        charAnimation.imageCount, 
        charAnimation.switchTime
    );
    sf::Texture *texture = &TextureManagement::getTexture(characterType);
    sf::Vector2i animation_size = animation.uvRect.getSize();
    sf::Vector2f size(30.0f, 40.0f);

    this->pSprite.setTexture(*texture);
    this->bbox.setSize(size);
    this->bbox.setFillColor(sf::Color::Transparent);
    this->bbox.setOutlineColor(sf::Color::Red);
    this->bbox.setOutlineThickness(3.0f);
    bbox.setOrigin(size.x / 2.0f, size.y / 2.0f);
    pSprite.setOrigin(animation_size.x / 2.0f, animation_size.y / 2.0f);
    pSprite.setPosition(200.0f, 200.0f);
    bbox.setPosition(pSprite.getPosition().x, pSprite.getPosition().y + 
                (animation.uvRect.getSize().y - bbox.getSize().y - 10.0f) / 2.0f );
    //this->pSprite.setScale(2.0f, 2.0f);
    
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

void Player::loseHP(int damage)
{
    this->stats.HP = 0 ? this->stats.HP - damage < 0: this->stats.HP - damage;
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
    this->pSprite.move(movement);
    this->bbox.move(movement);
}

void Player::draw(sf::RenderWindow *window)
{   
    window->draw(this->bbox);
    window->draw(this->pSprite);
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
    else
    {   
        this->updateMovement(deltaTime);
    }

    this->pSprite.setTextureRect(animation.uvRect);
    //std::cout << animation.uvRect.top<< " " << animation.uvRect.left << " " << animation.uvRect.width << " " << animation.uvRect.height << endl;
}

sf::Vector2f Player::getPosition()
{
    return pSprite.getPosition();
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
            movement.x /= float(sqrt(2.0));
            movement.y /= float(sqrt(2.0));
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
        currentState = AnimationState::Idle;
        row = 0;
    }
}
