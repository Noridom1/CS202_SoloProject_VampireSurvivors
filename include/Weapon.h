#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>

class Weapon {
public:
    Weapon();
    ~Weapon();
    
    virtual void render(sf::RenderWindow *window)  = 0;
    virtual void cast() = 0;

private:

};


#endif