#ifndef REALSOUNDLOADER_H
#define REALSOUNDLOADER_H

#include "ISoundLoader.h"
#include <unordered_map>

class RealSoundLoader : public ISoundLoader {
private:
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

public:
    const sf::SoundBuffer& getBuffer(const std::string& filePath) override {
        // Check if the sound buffer is already loaded
        if (soundBuffers.find(filePath) == soundBuffers.end()) {
            sf::SoundBuffer buffer;
            if (!buffer.loadFromFile(filePath)) {
                throw std::runtime_error("Error loading sound file: " + filePath);
            }
            soundBuffers[filePath] = std::move(buffer);
        }
        return soundBuffers[filePath];
    }
};

#endif
