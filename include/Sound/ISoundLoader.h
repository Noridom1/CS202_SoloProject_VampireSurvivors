#ifndef ISOUNDLOADER_H
#define ISOUNDLOADER_H

#include <SFML/Audio.hpp>
#include <string>

class ISoundLoader {
public:
    virtual ~ISoundLoader() = default;
    virtual const sf::SoundBuffer& getBuffer(const std::string& filePath) = 0;
};

#endif
