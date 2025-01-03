#ifndef EVENTS_H
#define EVENTS_H

#include "SFML/Audio.hpp"

enum class EventType {
    HPChanged,
    PlayerDeath,
    GainExp,
    LevelUp,
    PlayerMoving,
    Explosion,
    Pickup,
    ButtonClick,
    StartChooseWeapon,
    FinishChooseWeapon,
    GameOver,
    TimeChange,
};

class Event {
public:
    virtual ~Event() = default;
    virtual EventType getEvType() const = 0;
};

class HPChanged : public Event {
public:
    float damageAmount;
    sf::Vector2f& position;
    float maxHP, currentHP;
    bool onPlayer;
    HPChanged(float damage, sf::Vector2f& position, float curHP, float maxHP, bool onPlayer = false) 
        : damageAmount(damage), position(position), currentHP(curHP), maxHP(maxHP), onPlayer(onPlayer)  {}
    EventType getEvType() const override { return EventType::HPChanged; };
};

class GainExp : public Event {
public:
    float expAmount;
    float currentExp, maxExp;
    GainExp(float exp, float curExp, float maxExp) : expAmount(exp), currentExp(curExp), maxExp(maxExp) {}
    EventType getEvType() const override { return EventType::GainExp; };

};

class LevelUp : public Event {
public:
    LevelUp() {}
    EventType getEvType() const override { return EventType::LevelUp; };

};

class PlayerMoving : public Event {
public:
    PlayerMoving() {}
    EventType getEvType() const override { return EventType::PlayerMoving; };
};

class GetPickup : public Event {
public:
    GetPickup() {}
    EventType getEvType() const override { return EventType::Pickup; };

};

class StartChooseWeapon : public Event {
public:
    StartChooseWeapon() {}
    EventType getEvType() const override { return EventType::StartChooseWeapon; };

};

class FinishChooseWeapon : public Event {
public:
    FinishChooseWeapon() {}
    EventType getEvType() const override { return EventType::FinishChooseWeapon; };

};

class ButtonClick : public Event {
public:
    ButtonClick() {}
    EventType getEvType() const override { return EventType::ButtonClick; };

};

class GameOverEv : public Event {
public:
    GameOverEv() {}
    EventType getEvType() const override { return EventType::GameOver; };
};

class TimeChange : public Event {
public:
    int newTime;
    TimeChange(int newTime) : newTime(newTime) {}
    EventType getEvType() const override { return EventType::TimeChange; };
};

class Explosion : public Event {
public:
    float distance;
    Explosion(float dist) : distance(dist) {}
    EventType getEvType() const override { return EventType::Explosion; };
};

#endif 