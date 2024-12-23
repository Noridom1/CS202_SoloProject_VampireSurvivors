#ifndef NECROMANCER_H
#define NECROMANCER_H

#include "Player/Player.h"

class Necromancer : public Player {

public:
    Necromancer(sf::Vector2f pos);

    void setBoundingBox() override;

    void castSkill() override;
private:

};

#endif