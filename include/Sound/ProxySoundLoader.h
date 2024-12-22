#ifndef PROXYSOUNDLOADER_H
#define PROXYSOUNDLOADER_H

#include "ISoundLoader.h"
#include "RealSoundLoader.h"

class ProxySoundLoader : public ISoundLoader {
private:
    RealSoundLoader realLoader;

public:
    const sf::SoundBuffer& getBuffer(const std::string& filePath) override {
        // Delegate to the real loader for actual buffer management
        return realLoader.getBuffer(filePath);
    }
};

#endif
