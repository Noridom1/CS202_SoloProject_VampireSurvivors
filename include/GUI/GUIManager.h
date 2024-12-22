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
protected:
    vector<GUIComponent*> components; // Store all GUI components
    sf::Font font;
    sf::RenderWindow *window;

public:
    GUIManager(sf::RenderWindow *window) : window(window) {
        if (!font.loadFromFile("../assets/fonts/GUIfont.ttf")) {
            cout << "Cannot load GUI font\n";
        }
    }

    virtual ~GUIManager() {
        for (auto& component : components) {
            if (component) delete component;
        }
    }


    void addComponent(GUIComponent* component) {
        components.push_back(component);
    }

    virtual void update(float dt) {
        for (auto& component : components)
            component->update(dt);
    }

    virtual void render(sf::RenderWindow* window) {
        for (auto& component : components) {
            // if (component->isFixedWithWindow()) {
            //     component->setWorldPosition(window);
            // }
            component->render(window);
        }
    }

    virtual void handleEvent(const sf::Event& event) {
        for (auto& component : components)
            component->handleEvent(event);
        }


protected:
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