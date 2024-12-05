#ifndef SKILLSTEXTURE_H
#define SKILLSTEXTURE_H
#include "Texture.h"

#include <unordered_map>
#include <string>

using namespace std;

enum class SkillType {
    BLadeThunder,
};

const unordered_map<SkillType, string> skillTextures = {
    {SkillType::BLadeThunder, "../assets/textures/skills/BladeThunder.png"},
};

const unordered_map<SkillType, TexturesAnimation> skillAnimations = {
    {SkillType::BLadeThunder, {1, {6}, {0.1f}}},

};

#endif