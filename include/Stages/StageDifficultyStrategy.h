#ifndef STAGEDIFFICULTYSTRATEGY_H
#define STAGEDIFFICULTYSTRATEGY_H

#include <algorithm>
using namespace std;

class StageDifficultyStrategy {
public:
    virtual float getSpawningTime(float elapsedTime) = 0;     
    virtual int getMaxEnemies(float elapsedTime) = 0;        
    virtual float getEnemyStrengthMultiplier(float elapsedTime) = 0; 
    virtual float getWinningTime() = 0;
    virtual std::vector<int> getPickupDistribution() = 0;
    virtual ~StageDifficultyStrategy() {}
};

class Stage1Difficulty : public StageDifficultyStrategy {
public:
    float getSpawningTime(float elapsedTime) override {
        return max(2.5f - elapsedTime * 0.05f, 1.5f);
    }

    int getMaxEnemies(float elapsedTime) override {
        return 15 + static_cast<int>(elapsedTime * 0.2f);  // Max enemies increase from 10 to 15
    }

    float getEnemyStrengthMultiplier(float elapsedTime) override {
        return 1.0f + elapsedTime * 0.1f; // Enemy strength grows slowly
    }

    float getWinningTime() {
        return 180.f;
    }

    std::vector<int> getPickupDistribution() override {
        return {90, 10, 0};
    }

};

class Stage2Difficulty : public StageDifficultyStrategy {
public:
    float getSpawningTime(float elapsedTime) override {
        return max(2.5f - elapsedTime * 0.1f, 1.f);
    }

    int getMaxEnemies(float elapsedTime) override {
        return 20 + static_cast<int>(elapsedTime * 0.3f);  // Max enemies increase from 10 to 15
    }

    float getEnemyStrengthMultiplier(float elapsedTime) override {
        return 1.0f + elapsedTime * 0.15f; // Enemy strength grows slowly
    }

    float getWinningTime() {
        return 360.f;
    }

    std::vector<int> getPickupDistribution() override {
        return {95, 5, 0};
    }
};

class Stage3Difficulty : public StageDifficultyStrategy {
public:
    float getSpawningTime(float elapsedTime) override {
        return max(2.3f - elapsedTime * 0.15f, 0.8f);
    }

    int getMaxEnemies(float elapsedTime) override {
        return 20 + static_cast<int>(elapsedTime * 0.5f);  // Max enemies increase from 10 to 15
    }

    float getEnemyStrengthMultiplier(float elapsedTime) override {
        return 1.0f + elapsedTime * 0.2f; // Enemy strength grows slowly
    }

    float getWinningTime() {
        return 600.f;
    }

    std::vector<int> getPickupDistribution() override {
        return {100, 0, 0};
    }
};

#endif
