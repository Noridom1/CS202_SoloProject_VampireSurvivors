#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture *texture, unsigned stateCount, const vector<unsigned> &imageCount, const vector<float> &switchTime)
{
    this->stateCount = stateCount;
    this->imageCount = imageCount;
    this->switchTime = switchTime;

    this->totalTime = 0.0f;
    this->currentImage.x = 0;
    
    maxImageCount = 0;
    for (unsigned img_cnt : imageCount) {
        if (maxImageCount < img_cnt)
            maxImageCount = img_cnt;
    }
    std::cout << maxImageCount << endl;
    uvRect.width = texture->getSize().x / maxImageCount;
    uvRect.height = texture->getSize().y / stateCount;

}

void Animation::update(int row, float deltaTime, bool faceRight)
{
    finished = false;
    //std::cout << "row: " << row << endl;
    this->currentImage.y = row;
    this->totalTime += deltaTime;

    if (this->totalTime >= this->switchTime[row]) {  
        this->totalTime -= this->switchTime[row];
        currentImage.x++;
        if (currentImage.x >= imageCount[row]){
            finished = true;
            currentImage.x = 0;
        }
    }

    uvRect.top = this->currentImage.y * this->uvRect.height;

    if (faceRight){
        uvRect.width = abs(uvRect.width);
        uvRect.left = this->currentImage.x * this->uvRect.width;
    }
    else {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

}

bool Animation::isFinished(unsigned row)
{   
    // cout << row << endl;
    // cout << imageCount[row] - 1 << endl;
    // cout << switchTime[row] << endl;
    // cout << (currentImage.x == imageCount[row] - 1 && totalTime >= switchTime[row]) << endl;
    return finished;

}

void Animation::reset()
{
    this->currentImage.x = 0;
    if (uvRect.width > 0) {
        uvRect.left = this->currentImage.x * this->uvRect.width;
    }
    else {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
    }
    this->totalTime = 0;
}
