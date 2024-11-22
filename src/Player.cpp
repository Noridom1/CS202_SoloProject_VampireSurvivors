#include "Player.h"

Player::Player(CharacterType characterType)
{
    const auto& stats = characterStats.at(characterType);
    
    this->stats = CharacterStats(stats.HP, stats.armor, stats.base_damage, stats.move_speed);
    this->pSprite.setTexture(TextureManagement::getTexture(characterType));

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
    this->pPosition = pos;
}

void Player::move(sf::Vector2f new_pos)
{
    this->pSprite.setPosition(new_pos);
    this->setPosition(new_pos);
}

void Player::draw(sf::RenderWindow *window)
{
    window->draw(this->pSprite);
}
