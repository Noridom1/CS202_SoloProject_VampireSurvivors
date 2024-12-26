#ifndef STAGEDIFFICULTYSTRATEGY_H
#define STAGEDIFFICULTYSTRATEGY_H

#include <algorithm>
using namespace std;
#include "Enemy/EnemyFlyweightFactory.h"

class StageDifficultyStrategy {
public:
    virtual float getSpawningTime(float elapsedTime) = 0;
    virtual float getBossSpawningTime() = 0;
    virtual int getMaxEnemies(float elapsedTime) = 0;        
    virtual float getEnemyStrengthMultiplier(float elapsedTime) = 0; 
    virtual float getWinningTime() = 0;
    virtual vector<int> getPickupDistribution() = 0;
    virtual vector<EnemyType> getEnemyPool() = 0;
    virtual vector<EnemyType> getBosses() = 0;

    virtual ~StageDifficultyStrategy() {}
};

class Stage1Difficulty : public StageDifficultyStrategy {
public:
    float getSpawningTime(float elapsedTime) override {
        return max(2.5f - elapsedTime * 0.05f, 0.8f);
    }

    float getBossSpawningTime() override {
        return 60.f;
    }

    int getMaxEnemies(float elapsedTime) override {
        return 25 + static_cast<int>(elapsedTime * 0.2f);
    }

    float getEnemyStrengthMultiplier(float elapsedTime) override {
        return min(4.f, 1.0f + elapsedTime * 0.01f);

    }

    float getWinningTime() override {
        return 180.f;
    }

    vector<int> getPickupDistribution() override {
        return {90, 10, 0};
    }

    vector<EnemyType> getEnemyPool() override {
        // Stage 1 has Ghost and Microwave as basic enemies, and Demon as the boss
        vector<EnemyType> pool = {EnemyType::Ghost, EnemyType::Microwave};
        return pool;
    }

    vector<EnemyType> getBosses() override {
        vector<EnemyType> bosses = {EnemyType::Demon};
        return bosses;
    }
};

class Stage2Difficulty : public StageDifficultyStrategy {
public:
    float getSpawningTime(float elapsedTime) override {
        return max(2.5f - elapsedTime * 0.1f, 0.5f);
    }

    float getBossSpawningTime() override {
        return 80.f;
    }

    int getMaxEnemies(float elapsedTime) override {
        return 25 + static_cast<int>(elapsedTime * 0.2f);
    }

    float getEnemyStrengthMultiplier(float elapsedTime) override {
        return min(5.f, 1.0f + elapsedTime * 0.008f);
    }

    float getWinningTime() override {
        return 360.f;
    }

    vector<int> getPickupDistribution() override {
        return {95, 5, 0};
    }

    vector<EnemyType> getEnemyPool() override {
        vector<EnemyType> pool = {EnemyType::Ghost, EnemyType::Microwave};
        return pool;
    }

    vector<EnemyType> getBosses() override {
        vector<EnemyType> bosses = {EnemyType::BringerOfDeath};
        return bosses;
    }
};

class Stage3Difficulty : public StageDifficultyStrategy {
public:
    float getSpawningTime(float elapsedTime) override {
        return max(2.3f - elapsedTime * 0.12f, 0.3f);
    }

    float getBossSpawningTime() override {
        return 60.f;
    }

    int getMaxEnemies(float elapsedTime) override {
        return 25 + static_cast<int>(elapsedTime * 0.5f);
    }

    float getEnemyStrengthMultiplier(float elapsedTime) override {
        return min(6.f, 1.0f + elapsedTime * 0.01f);
    }

    float getWinningTime() override {
        return 600.f;
    }

    vector<int> getPickupDistribution() override {
        return {100, 0, 0};
    }

    vector<EnemyType> getEnemyPool() override {
        // Stage 3 has Ghost and Microwave as basic enemies, and two BringerOfDeath as bosses
        vector<EnemyType> pool = {EnemyType::Ghost, EnemyType::Microwave};
        return pool;
    }

    vector<EnemyType> getBosses() override {
        vector<EnemyType> bosses = {EnemyType::Demon, EnemyType::BringerOfDeath};
        return bosses;
    }
};


#endif
