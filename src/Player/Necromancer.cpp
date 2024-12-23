#include "Player/Necromancer.h"

Necromancer::Necromancer(sf::Vector2f pos) : 
    Player(CharacterType::Necromancer, pos)
{
    this->setBoundingBox();
}

void Necromancer::setBoundingBox()
{
    float width = 25.f, height = 35.f;
    this->boundingBox = sf::FloatRect(
        this->position.x - width / 2.f,
        this->position.y - height / 2.f + 20.f,
        width,
        height
    );
    this->pSprite.setScale(0.8f, 0.8f);
}

void Necromancer::castSkill()
{

}
