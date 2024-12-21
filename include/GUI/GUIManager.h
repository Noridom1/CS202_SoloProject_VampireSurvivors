#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "HPBar.h"
#include "ExpBar.h"
#include <vector>

enum class State {
    MENU,
    GAMEPLAY,
    EXIT
};

class GUIManager {
private:
    vector<GUIComponent*> components; // Store all GUI components

public:
    GUIManager(State state) {
        if (state == State::GAMEPLAY) {
            addComponent(new HPBar(10.f, 10.f, 1000.f, 20.f));
            addComponent(new ExperienceBar(10.f, 40.f, 1000.f, 20.f));
        }
    }

    void addComponent(GUIComponent* component) {
        components.push_back(component);
    }

    void update(float dt) {
        for (auto& component : components)
            component->update(dt);
    }

    void render(sf::RenderWindow* window, sf::View &view) {
        for (auto& component : components) {
            if (component->isFixedWithWindow()) {
                component->setWorldPosition(window);
            }
            component->render(window);
        }
    }

    void handleEvent(const sf::Event& event) {
        for (auto& component : components)
            component->handleEvent(event);
        }

    ~GUIManager() {
        for (auto& component : components) {
            if (component) delete component;
        }
    }

    HPBar* getHPBar() {
        auto hpBar = getComponentByIndex<HPBar>(0);
        return hpBar;
    }

    
    ExperienceBar* getExpBar() {
        auto expBar = getComponentByIndex<ExperienceBar>(1);
        cout << "GetEXPBar\n";
        return expBar;
    }

private:
    template <typename T>
    T* getComponentByIndex(size_t index) {
        if (index >= components.size()) {
            throw std::out_of_range("Index out of range");
        }

        // Cast the component to the desired type
        T* component = dynamic_cast<T*>(components[index]);
        if (!component) {
            throw std::runtime_error("Component at index is not of the requested type");
        }

        return component;
    }
};


#endif