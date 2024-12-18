#include "CollisionHandling/Quadtree.h"
#include <iostream>
#include <memory>
#include <array>
#include <algorithm>

Quadtree::Quadtree(int level, sf::FloatRect bounds) : level(level), bounds(bounds) {}

Quadtree::~Quadtree()
{
    clear();
}

void Quadtree::clear()
{
    for (auto &node : nodes)
    {
        if (node)
        {
            node->clear();
            node.reset(); // Ensure the unique_ptr is reset
        }
    }
    nodes.clear();
    objects.clear();
}

void Quadtree::split()
{
    if (!nodes.empty())
        return; // Already split

    float subWidth = bounds.width / 2.f;
    float subHeight = bounds.height / 2.f;

    if (subWidth <= 0 || subHeight <= 0)
        return;

    float x = bounds.left;
    float y = bounds.top;

    sf::FloatRect quadrantRects[4] = {
        {x, y, subWidth, subHeight},                       // Top-left
        {x + subWidth, y, subWidth, subHeight},            // Top-right
        {x, y + subHeight, subWidth, subHeight},           // Bottom-left
        {x + subWidth, y + subHeight, subWidth, subHeight} // Bottom-right
    };

    nodes.resize(4);
    for (int i = 0; i < 4; ++i)
    {
        nodes[i] = std::make_unique<Quadtree>(level + 1, quadrantRects[i]);
    }

    for (auto *object : objects)
    {
        int index = getIndex(object);
        if (index != -1)
        {
            nodes[index]->insert(object);
        }
    }

    // Remove objects moved to children
    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [this](Entity *obj)
            {
                // for (const auto &node : nodes)
                // {
                //     if (node && node->getIndex(obj) != -1)
                //         if (obj->id == 68) {
                //             std::cout << node->level;
                //         }
                //         return true;
                // }
                // return false;

                return this->getIndex(obj) != -1;
            }),
            objects.end()
    );
}

void Quadtree::merge()
{
    if (nodes.empty())
        return;

    const int mergeThreshold = 8; // Same threshold for merging
    int totalObjects = static_cast<int>(objects.size());

    // Check if children can be merged
    bool canMerge = true;
    for (const auto &node : nodes)
    {
        if (node)
        {
            totalObjects += static_cast<int>(node->objects.size());
            if (!node->nodes.empty())
            {
                canMerge = false; // Prevent merging if any child is further split
            }
        }
    }

    if (canMerge && totalObjects <= mergeThreshold)
    {
        for (auto &node : nodes)
        {
            if (node)
            {
                objects.insert(objects.end(), node->objects.begin(), node->objects.end());
                node.reset(); // Delete child node
            }
        }
        nodes.clear();
    }
}

int Quadtree::getIndex(Entity *entity)
{
    // Dynamically calculate midpoints for each node
    double verticalMidpoint = bounds.left + bounds.width / 2.0;
    double horizontalMidpoint = bounds.top + bounds.height / 2.0;

    sf::FloatRect entityBounds = entity->getBoundingBox();

    bool fitsInTop = entityBounds.top + entityBounds.height < horizontalMidpoint;
    bool fitsInBottom = entityBounds.top >= horizontalMidpoint;

    bool fitsInLeft = entityBounds.left + entityBounds.width < verticalMidpoint;
    bool fitsInRight = entityBounds.left >= verticalMidpoint;

    // If the object spans multiple quadrants, return -1
    if ((fitsInTop && fitsInBottom) || (fitsInLeft && fitsInRight))
        return -1;

    if (fitsInTop)
    {
        if (fitsInLeft)
            return 0; // Top-left
        else if (fitsInRight)
            return 1; // Top-right
    }
    else if (fitsInBottom)
    {
        if (fitsInLeft)
            return 2; // Bottom-left
        else if (fitsInRight)
            return 3; // Bottom-right
    }

    return -1; // Overlapping multiple quadrants or undefined case
}


void Quadtree::insert(Entity *entity)
{   
    if (!nodes.empty())
    {
        int index = getIndex(entity);
        if (index != -1 && index < static_cast<int>(nodes.size()) && nodes[index])
        {
            nodes[index]->insert(entity);
            return;
        }
    }

    objects.push_back(entity);
 
    if (level >= maxLevel)
    {
        return;
    }

    if (objects.size() > splitThreshold && nodes.empty())
    {
        split();
    }
    else if (!nodes.empty())
    {
        merge(); // Attempt to merge if objects fall below the merge threshold
    }

}

void Quadtree::retrieve(std::vector<Entity *> &returnObjects, Entity *entity)
{
    // Add all objects in the current node
    returnObjects.insert(returnObjects.end(), objects.begin(), objects.end());

    // Ensure the nodes vector is not empty
    if (!nodes.empty())
    {
        int index = getIndex(entity);
        

        if (index != -1)
        {
            // Retrieve from the specific child node if it exists
            if (index < static_cast<int>(nodes.size()) && nodes[index])
            {
                nodes[index]->retrieve(returnObjects, entity);
            }
        }
        else
        {
            // If the object overlaps multiple quadrants, retrieve from all children
            for (const auto &node : nodes)
            {
                if (node)
                { // Check if the node is not null
                    node->retrieve(returnObjects, entity);
                }
            }
        }
    }
}

void Quadtree::retrieveNearBy(std::vector<Entity *> &returnObjects, Entity *entity, EntityType type)
{
    sf::FloatRect queryBounds = entity->getBoundingBox();

    // Add objects in the current node that intersect with the query bounds
    for (auto *object : objects)
    {
        if (queryBounds.intersects(object->getBoundingBox()) && 
            (type == EntityType::None || type == object->getType()))
        {
            returnObjects.push_back(object);
        }
    }

    // If there are no child nodes, stop here
    if (nodes.empty())
    {
        return;
    }

    // Get the index of the child node that fully contains the query bounds
    int index = getIndex(entity);

    if (index != -1 && nodes[index])
    {
        // The query region fits completely within one child quadrant
        nodes[index]->retrieve(returnObjects, entity);
    }
    else
    {
        // The query region spans multiple quadrants; check all child nodes
        for (const auto &node : nodes)
        {
            if (node && queryBounds.intersects(node->bounds))
            {
                node->retrieve(returnObjects, entity);
            }
        }
    }

}
void Quadtree::draw(sf::RenderWindow &window, float zoomFactor, float panX, float panY)
{
    // Draw the bounds of the current node
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left + panX, bounds.top + panY);
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(1.0f / zoomFactor); // Adjust thickness based on zoom
    rect.setFillColor(sf::Color::Transparent);

    window.draw(rect);

    // Recursively draw child nodes
    for (const auto &node : nodes)
    {
        if (node)
        {
            node->draw(window, zoomFactor, panX, panY);
        }
    }

}
