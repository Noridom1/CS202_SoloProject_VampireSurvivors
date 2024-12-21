#ifndef PICKUPFLYWEIGHTFACTORY_H
#define PICKUPFLYWEIGHTFACTORY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include "Animation.h"
#include "Image.h"
#include "Pickups/Pickup.h"

static const std::unordered_map<PickupType, std::string> PickupPaths = {
        { PickupType::ExpGem, "../assets/textures/pickups/ExpGem.png" },
        { PickupType::Chicken, "../assets/textures/pickups/Chicken.png"},
        { PickupType::Chest, "../assets/textures/pickups/Chest.png"},
        //{ EnemyType::Bullet,    "../Bullet.png" },
        //{ ProjectileType::Laser,     "../Laser.png" }
};

const unordered_map<PickupType, TexturesAnimation> pickupAnimations = {
    {PickupType::ExpGem, {4, {6, 4, 7, 7}, {0.06f, 0.1f, 0.1f, 0.1f}}},
    {PickupType::Chicken, {5, {20, 6, 6, 12, 6}, {0.05f, 0.05f, 0.1f, 0.2f, 0.1f}}},
    {PickupType::Chest, {5, {5, 6, 15, 4, 8}, {0.1f, 0.1f, 0.1f, 0.05f, 0.1f}}}

};

class PickupFlyweightFactory {
public:
    static Image& getPickupImg(PickupType type) {
        static std::unordered_map<PickupType, std::unique_ptr<Image>> pickupImage;

        string filename = PickupPaths.at(type);
        if (pickupImage.find(type) == pickupImage.end()) {
            pickupImage[type] = std::make_unique<Image>(filename);
        }

        return *pickupImage[type];
    }
};


#endif