#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : Entity {
    public:
    
    private:
        int HP;
        int armor;
        int base_damage;
        int move_speed;
        int exp;
        int level;
};

#endif