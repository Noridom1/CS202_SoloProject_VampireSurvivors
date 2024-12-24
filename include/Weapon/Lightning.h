#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "Weapon.h"

class Lightning : public Weapon {

public:
    Lightning(Player *player);

    ~Lightning() {};

    void levelUp() override;
    
    void update(sf::RenderWindow *window, Player *player, float deltaTime) override ;

    vector<Entity*> getRandomEnemyPos();

    WeaponType getType() const override;

    void cast();

private:
    int numEnemyCast;
    float totalTime;
    float effectiveRadius;

};

#endif