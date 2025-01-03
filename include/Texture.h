#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <unordered_map>
#include "Player/Characters.h"
#include "Skills/SkillsTexture.h"
#include "Enemy/EnemyFlyweightFactory.h"

using namespace std;

class TextureManagement {
public:
    static unordered_map<string, sf::Texture> textures;

    static sf::Texture& getTextureByString(string filename) {
        if(textures.find(filename) == textures.end()) {
            sf::Texture texture;
            try {
                if (!texture.loadFromFile(filename)){
                    throw runtime_error("Failed to load texture: " + filename);
                }
            }
            catch (string str) {
                cout << str << endl;
            }
            textures[filename] = move(texture);
        }
        return textures[filename];

    }
    static sf::Texture& getTexture(CharacterType characterType){
        const auto& filename = characterTextures.at(characterType);

        if (textures.find(filename) == textures.end()){
            sf::Texture texture;
            cout << "characterType: " << static_cast<int>(characterType) << endl;
            try {
                if (!texture.loadFromFile(filename)){
                    throw runtime_error("Failed to load texture: " + filename);
                }
            }
            catch (string str) {
                cout << str << endl;
            }
            
            textures[filename] = move(texture);
        }
        return textures[filename];
    }   

    static sf::Texture& getSkillTexture(SkillType skillType){
        const auto& filename = skillTextures.at(skillType);

        if (textures.find(filename) == textures.end()){
            sf::Texture texture;
            if (!texture.loadFromFile(filename)){
                throw runtime_error("Failed to load texture: " + filename);
            }
            textures[filename]= move(texture);
        }
        return textures[filename];
    }   

    static sf::Texture& getEnemyTexture(EnemyType enemyType) {
        const auto filename = EnemyPaths.at(enemyType);
        if (textures.find(filename) == textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile(filename)){
                throw runtime_error("Failed to load texture: " + filename);
            }
            textures[filename]= move(texture);
        }
        return textures[filename];
    }
};

#endif