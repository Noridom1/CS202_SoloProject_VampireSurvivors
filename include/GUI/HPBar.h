#ifndef HPBAR_H
#define HPBAR_H

#include "ProgressBar.h"

class HPBar : public ProgressBar {
public:
    HPBar(float wdPosX, float wdPosY, sf::Font &font)
        : ProgressBar(wdPosX, wdPosY, font)
    {   
        this->offset = sf::Vector2f(8.f, 8.f);
        fill = new Image("../assets/GUI/HP_fill.png");
        fill->setPosition(sf::Vector2f(wdPosX + offset.x, wdPosY + offset.y));
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
