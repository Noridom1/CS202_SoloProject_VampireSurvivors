#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

struct TexturesAnimation {
    unsigned numSprites;
    vector<unsigned> imageCount;
    vector<float> switchTime;
};

class Animation {
public:
    Animation() = default;
    Animation(sf::Texture *texture, unsigned stateCount, const vector<unsigned> &imageCount, const vector<float> &switchTime);

    void update(int row, float deltaTime, bool faceRight);
    bool isFinished(unsigned row);
    void reset();

public:
    sf::IntRect uvRect;

private:
    unsigned stateCount;
    sf::Vector2u currentImage;

    unsigned maxImageCount;
    float totalTime;
    vector<unsigned> imageCount;
    vector<float> switchTime;
    bool finished = false;

};


#endif