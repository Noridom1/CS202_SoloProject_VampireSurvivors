#ifndef KAEL_H
#define KAEL_H

#include "Player/Player.h"

class Kael : public Player {

public:
    Kael(sf::Vector2f pos);

    void setBoundingBox() override;

    void castSkill() override;
private:

};

#endif