#ifndef EXPERIENCEBAR_H
#define EXPERIENCEBAR_H

#include "ProgressBar.h"

class ExperienceBar : public ProgressBar {
public:
    ExperienceBar(float x, float y, sf::Font &font)
        : ProgressBar(x, y, font) 
    {
        this->offset = sf::Vector2f(8.f, 8.f);
        fill = new Image("../assets/GUI/GamePlaying/Exp_fill.png");  // Blue for Experience bar
        fill->setPosition(sf::Vector2f(x + offset.x, y + offset.y));
        this->setProgress(0.f);
    }

    void updateExperience(float currentXP, float maxXP) {
        setProgress(currentXP / maxXP);  // Update based on current and max XP
    }

    void onNotify(const Event *event) override {
        if (event->getEvType() == EventType::GainExp) {
            const GainExp* gainExpEvent = dynamic_cast<const GainExp*>(event);
            if (gainExpEvent) {
                updateExperience(gainExpEvent->currentExp, gainExpEvent->maxExp);
            }
        }
    }


};

#endif
