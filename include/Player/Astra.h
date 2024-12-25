#ifndef ASTRA_H
#define ASTRA_H

#include "Player/Player.h"

class Astra : public Player {

public:
    Astra(sf::Vector2f pos);

    void setBoundingBox() override;

    void castSkill() override;
private:

};

#endif