#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <memory> 

#include "Entity/Entity.h"
#include <SFML/Graphics.hpp>

class Quadtree
{
private:
    int level;
    sf::FloatRect bounds;
    std::vector<Entity *> objects;
    std::vector<std::unique_ptr<Quadtree>> nodes; // Use smart pointers

    void split(); // Splits the node into four child nodes
    void merge(); // Merges child nodes back into the parent node
    int getIndex(Entity *entity); // Determines which child node the circle belongs to

    const int splitThreshold = 10; // Split if objects exceed this threshold
    const int maxLevel = 10;      // Limit quadtree depth to prevent excessive splitting


public:
    Quadtree(int level, sf::FloatRect bounds);
    ~Quadtree();

    void clear(); // Clears the current node and its children
    void insert(Entity *entity); // Inserts a circle into the quadtree
    void retrieve(std::vector<Entity *> &returnObjects, Entity *entity); // Retrieves all circles that might collide with the given circle
    void retrieveNearBy(std::vector<Entity *> &returnObjects, Entity *entity, EntityType type = EntityType::None);
    void draw(sf::RenderWindow &window, float zoomFactor=1.f, float panX=0.0f, float panY=0.f); // Draw Quadtree strcuture
};

#endif // QUADTREE_H