#ifndef PICKUPFACTORY_H
#define PICKUPFACTORY_H

#include "ExpGem.h"
#include "Chicken.h"
#include "Chest.h"


class PickupFactory {
public:
    static Pickup* createPickup(PickupType type, sf::Vector2f startPos, float lifetime, float timeScale) {
        if (type == PickupType::ExpGem) {
            return new ExpGem(startPos, lifetime, timeScale);
        } 
        else if (type == PickupType::Chicken) {
            return new Chicken(startPos, lifetime, timeScale);
        }
        else if (type == PickupType::Chest) {
            return new Chest(startPos, lifetime, timeScale);
        }
        else {
            throw std::invalid_argument("Unknown pickup type!");
        }
    }
private:

};


#endif