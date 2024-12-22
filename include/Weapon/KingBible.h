#ifndef KINGBIBLE_H
#define KINGBIBLE_H

#include "Weapon.h"

class KingBible : public Weapon {

public:
    KingBible(Player *player);
    //void draw(sf::RenderWindow *window) override;
    void cast();

    void update(sf::RenderWindow *window, Player *player, float deltaTime);

    void levelUp() override;

    WeaponType getType() const override { return WeaponType::KingBible; }


private:
    float move_speed;
    unsigned num_projectiles;
    unsigned num_casted;
    float delayedTime;
    float totalTime;

    float duration;
};

#endif