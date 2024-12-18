#include "Enemy/Ghost.h"
#include <string>

using namespace std;

Ghost::Ghost(sf::Vector2f pos) :
    Enemy(pos, 20.f, 5.f, 100.f), isSpawning(true), isHurting(false), isVanishing(false)
{   
    string filename = EnemyPaths.at(EnemyType::Ghost);
    TexturesAnimation textureAnimation = EnemyAnimations.at(EnemyType::Ghost);
    this->img = new Image(filename);
    this->animation = Animation(
        &img->getTexture(),
        4,
        {6, 4, 7, 7},
        {0.1f, 0.1f, 0.1f, 0.1f}
    );

    sf::Vector2i animation_size = animation.uvRect.getSize();
    this->img->getSprite().setOrigin(animation_size.x / 2.f, animation_size.y / 2.f);
    this->setBoundingBox();

    cout << "Init a Ghost!\n";
}

Ghost::~Ghost()
{
    delete this->img;
}

void Ghost::updateMovement(float deltaTime, sf::Vector2f playerPos)
{
    sf::Vector2f movement = playerPos - this->position;

    float magnitude = sqrt(movement.x * movement.x + movement.y * movement.y);

    if (magnitude)
        movement /= magnitude;
    movement *= move_speed * deltaTime;

    if (std::abs(movement.x) > 0.01f) { // Add a small threshold for precision issues
        faceRight = (movement.x > 0) ? textureDirection : !textureDirection;
    }

    if (isHurting) {
        row = 2;
    }

    if(movement.x && movement.y) {
        movement /= static_cast<float>(sqrt(2));
    }

    this->move(movement);
    this->animation.update(row, deltaTime, faceRight);
    if (isHurting && animation.isFinished(row)) {
        row = 1;
        isHurting = false;
    }
}

void Ghost::setBoundingBox()
{
    this->boundingBox = sf::FloatRect(0, 0, 20.f, 30.f);
    this->boundingBox.left = this->position.x - this->boundingBox.width / 2.f;
    this->boundingBox.top = this->position.y - this->boundingBox.height / 2.f;
}

void Ghost::update(float deltaTime, sf::Vector2f playerPos)
{
    if (isSpawning) {
        row = 0;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isSpawning = false;
        }
    }

    else if (isVanishing) {
        row = 3;
        animation.update(row, deltaTime, faceRight);
        if (animation.isFinished(row)) {
            row = 1;
            isVanishing = false;
            this->markDelete();
        }
    }

    else {
        updateMovement(deltaTime, playerPos);
    }
    this->img->getSprite().setTextureRect(animation.uvRect);
}
