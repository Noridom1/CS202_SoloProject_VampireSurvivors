#ifndef HPBAR_H
#define HPBAR_H

#include "ProgressBar.h"

class HPBar : public ProgressBar{
public:
    HPBar(float wdPosX, float wdPosY, float width, float height)
        : ProgressBar(wdPosX, wdPosY, width, height)
    {
        // Set a red color for HP
        fill.setFillColor(sf::Color(255, 0, 0));  // Red for HP bar
        this->setProgress(1.f);
    }

    void onNotify(const Event *event) override {
        if (event->getEvType() == EventType::HPChanged) {
            const HPChanged* hpChangedEvent = dynamic_cast<const HPChanged*>(event);
            if (hpChangedEvent) {
                setProgress(hpChangedEvent->currentHP / hpChangedEvent->maxHP);
            }
        }
    }

};

#endif
