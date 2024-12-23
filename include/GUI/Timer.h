#ifndef TIMER_H
#define TIMER_H

#include "Image.h"

class Timer {

public:
    Timer(float wdPosX, float wdPosY, sf::Font &font) {

        this->background = new Image("../assets/GUI/GamePlaying/TimerBG.png");
        this->background->setPosition(wdPosX, wdPosY);

        time.setString("0:00");
        time.setCharacterSize(30);
        time.setFillColor(sf::Color(253, 226, 148));
        time.setPosition(wdPosX + 60.f, wdPosY + 10.f);
        time.setFont(font);

    }
    ~Timer() {
        delete this->background;
    }

    void update(float time) {
        int minute = int(time) / 60;
        int second = int(time) % 60;
        this->time.setString(to_string(minute) + ":" + (second < 10 ? "0" : "") + to_string(second));
    }

    void render(sf::RenderWindow *window) {
        background->draw(window);
        window->draw(time);
    }

private:
    Image* background;
    sf::Text time;

};

#endif