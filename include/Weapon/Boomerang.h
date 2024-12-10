#ifndef BOOMERANG_H
#define BOOMERANG_H

#include "Weapon.h"

class Boomerang : public Weapon {

public:
    Boomerang();
    //void draw(sf::RenderWindow *window) override;
    void cast(sf::Vector2f position, sf::Vector2f direction) override;

    void update(sf::RenderWindow *window, Player *player, float deltaTime);

    void levelUp() override;

private:
    float move_speed;
    unsigned num_projectiles;
    unsigned num_casted;
    float delayedTime;
    float totalTime;
    bool isCasting;
};


#endif 