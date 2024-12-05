#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Characters.h"
#include "Texture.h"
#include "Animation.h"
#include "Skills/Skill.h"
#include "Skills/BladeThunder.h"

class Player : Entity {
public:
    enum class AnimationState {
        Idle,
        Move,
        Attack
    }; 

    Player() = default;
    Player(CharacterType characterType);
    ~Player();


    void levelUp();
    void loseHP(int damage);

    void setArmor(int armor);
    void setBaseDamage(int base_damage);
    void setMoveSpeed(float move_speed);
    void setPosition(sf::Vector2f pos);

    void castSkill();

    void move(sf::Vector2f new_pos);
    void draw(sf::RenderWindow *window);
    void update(float deltaTime);
    void updateMovement(float deltaTime);
    void updateAttack(float deltaTime);
    sf::Vector2f getPosition();
    
private:
    CharacterStats stats;
    int exp;
    int level;
    Skill *skill;

    sf::Texture *texture;
    sf::Sprite pSprite;
    Animation animation;
    sf::Vector2f pPosition;
    sf::RectangleShape bbox;
    bool faceRight;
    unsigned int row;
    
    AnimationState currentState;
    bool attackInProgress;

    float totalTime;
    float attackTime;

        
};

#endif