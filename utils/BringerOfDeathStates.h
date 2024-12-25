#ifndef BRINGEROFDEATHSTATES_H
#define BRINGEROFDEATHSTATES_H

// #include "BringerOfDeath.h"
// #include <memory>

// class SpawingState;
// class MovingState;

// class BODState {
// public:
//     explicit BODState(unsigned row) : animationRow(row) {}
//     virtual ~BODState() = default;

//     virtual void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) = 0;
//     virtual void onHit(BringerOfDeath& enemy) {}

//     unsigned getAnimationRow() const { return animationRow; } // Provide row access

// protected:
//     unsigned animationRow;
// };

// class SpawningState : public BODState {
// public:
//     SpawningState() : BODState(0) {} // Row 0 for spawning animation

//     void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override {
//         enemy.updateAnimation(getAnimationRow(), deltaTime, enemy.isFacingRight());
//         if (enemy.isAnimationFinished(getAnimationRow())) {
//             enemy.setState(std::make_unique<MovingState>());
//         }
//     }
// };

// class MovingState : public BODState {
// public:
//     MovingState() : BODState(1) {}

//     void update(float deltaTime, BringerOfDeath& enemy, sf::Vector2f playerPos) override {
//         enemy.updateAnimation(getAnimationRow(), deltaTime, enemy.isFacingRight());
//     }
// };

#endif