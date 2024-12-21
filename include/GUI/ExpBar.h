#ifndef EXPERIENCEBAR_H
#define EXPERIENCEBAR_H

#include "ProgressBar.h"

class ExperienceBar : public ProgressBar {
public:
    ExperienceBar(float x, float y, float width, float height)
        : ProgressBar(x, y, width, height) {
        // Set a blue color for Experience
        fill.setFillColor(sf::Color::Yellow);  // Blue for Experience bar
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
