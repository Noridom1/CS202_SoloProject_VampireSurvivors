#ifndef LUCY_H
#define LUCY_H

#include "Player/Player.h"

class Lucy : public Player {

public:
    Lucy(sf::Vector2f pos);

    void setBoundingBox() override;

    void castSkill() override;
private:

};

#endif