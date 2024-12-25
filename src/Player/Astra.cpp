#include "Player/Astra.h"

Astra::Astra(sf::Vector2f pos) : 
    Player(CharacterType::Astra, pos)
{
    this->setBoundingBox();
}

void Astra::setBoundingBox()
{
    float width = 25.f, height = 35.f;
    this->boundingBox = sf::FloatRect(
        this->position.x - width / 2.f,
        this->position.y - height / 2.f + 20.f,
        width,
        height
    );
    //this->pSprite.setScale(0.8f, 0.8f);
}

void Astra::castSkill()
{

}
