#include "Player/Lucy.h"

Lucy::Lucy(sf::Vector2f pos) : 
    Player(CharacterType::Lucy, pos)
{
    this->setBoundingBox();
}

void Lucy::setBoundingBox()
{
    float width = 25.f, height = 35.f;
    this->boundingBox = sf::FloatRect(
        this->position.x - width / 2.f,
        this->position.y - height / 2.f + 10.f,
        width,
        height
    );
}

void Lucy::castSkill()
{

}
