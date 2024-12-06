#ifndef BOOMERANG_H
#define BOOMERANG_H

#include "Weapon.h"

class Boomerang : public Weapon {

public:
    Boomerang() : 
        Weapon(10.0f, 2.0f), 
        move_speed(500.0f), 
        num_projectiles(1),
        delayedTime(0.15f),
        totalTime(0.0f),
        isCasting(false)
        {};
    //void draw(sf::RenderWindow *window) override;
    void cast(sf::Vector2f position, sf::Vector2f direction) override {
        ProjectileManager::getInstance().spawnProjectile(ProjectileType::Boomerang, position, direction, move_speed);
    }

    void update(sf::RenderWindow *window, Player *player, float deltaTime) {
        if (isCasting) {
            totalTime += deltaTime;
            if (totalTime >= delayedTime) {
                totalTime -= delayedTime;
                //sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                sf::Vector2i mouseWindowPos = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePos = window->mapPixelToCoords(mouseWindowPos, window->getView()); 
                sf::Vector2f position = player->getPosition();
                sf::Vector2f direction = sf::Vector2f(mousePos.x, mousePos.y) - position;
                this->cast(position, direction);
                num_casted++;
            }
            if (num_casted >= num_projectiles) {
                num_casted = 0;
                isCasting = false;
                totalTime = 0;
            }
        }
        else {
            totalTime += deltaTime;
            if (totalTime >= cooldown) {
                totalTime -= cooldown ;
                isCasting = true;
                sf::Vector2i mouseWindowPos = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePos = window->mapPixelToCoords(mouseWindowPos, window->getView()); 
                sf::Vector2f position = player->getPosition();
                sf::Vector2f direction = sf::Vector2f(mousePos.x, mousePos.y) - position;
                this->cast(position, direction);
                num_casted++;
            }
        }
        
    }

    void levelUp() override {
        this->level++;
        this->move_speed *= 1.2f;
        this->damage *= 1.2f;
        this->num_projectiles++;
        cout << "Boomerang::levelUp()\n";
    }

private:
    float move_speed;
    unsigned num_projectiles;
    unsigned num_casted;
    float delayedTime;
    float totalTime;
    bool isCasting;
};


#endif 