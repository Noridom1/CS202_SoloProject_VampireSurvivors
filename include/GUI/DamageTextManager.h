#ifndef DAMAGETEXTMANAGET_H
#define DAMAGETEXTMANAGET_H

#include "FloatingText.h"
#include "GUIManager.h"
#include "Observer.h"
#include "GUI/Events.h"

// DamageTextManager.h
class DamageTextManager : public Observer {
private:
    sf::Font font;
    GUIManager *guiManager;

public:
    // Adjust constructor to accept a shared pointer to GUIManager
    DamageTextManager(GUIManager* manager) 
        : guiManager(manager) {
        if (!font.loadFromFile("../assets/fonts/Poppins-Bold.ttf")) {
            throw std::runtime_error("Failed to load font");
        }
        //cout << "Init a Damage Text Manager\n"; 
    }

    void onNotify(const Event *event) override {
        if (event->getEvType() == EventType::HPChanged) {
            const HPChanged* hpChangedEvent = dynamic_cast<const HPChanged*>(event);
            if (hpChangedEvent) {
                guiManager->addComponent(new FloatingText(
                    std::to_string(int(hpChangedEvent->damageAmount)), font,
                    hpChangedEvent->position, hpChangedEvent->onPlayer ? sf::Color::Red : sf::Color::White, 1.5f
                ));
            }
        }
    }
};



#endif