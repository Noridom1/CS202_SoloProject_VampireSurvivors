#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include <memory>
#include "GUI/Observer.h"
#include "GUI/Events.h"
#include "ProxySoundLoader.h"
#include <SFML/Audio.hpp>

class SoundManager : public Observer {
private:
    std::unique_ptr<ISoundLoader> soundLoader;

    sf::Sound hitSound;
    sf::Sound explosionSound;
    sf::Sound levelUpSound;
    sf::Sound playerMovingSound;
    sf::Sound expPickupSound;
    sf::Sound buttonClickSound;


    sf::Music backgroundMusic; // Use sf::Music for background music
    std::vector<std::string> playlist; // Playlist of music tracks
    int currentTrackIndex = 0; // Track currently playing

public:

    SoundManager() : soundLoader(std::make_unique<ProxySoundLoader>()) {
        playlist = {
            "../assets/sounds/musics/BG1.wav",
            "../assets/sounds/musics/BG2.wav",
            "../assets/sounds/musics/BG3.wav"
        };

        // Start playing the first track
        if (!playlist.empty()) {
            playMusic(playlist[currentTrackIndex]);
        }
    }

    void updateBackgroundMusic() {
        // Check if the music has stopped
        if (backgroundMusic.getStatus() == sf::Music::Stopped) {
            currentTrackIndex = (currentTrackIndex + 1) % playlist.size(); // Loop through playlist
            playMusic(playlist[currentTrackIndex]);
        }
    }

    void playMusic(const std::string& trackPath) {
        if (!backgroundMusic.openFromFile(trackPath)) {
            std::cerr << "Error loading " << trackPath << std::endl;
            return;
        }
        backgroundMusic.setVolume(10.f);
        backgroundMusic.play();
    }

    void playHitSound() {
        hitSound.setBuffer(soundLoader->getBuffer("../assets/sounds/Hit1.wav"));
        hitSound.play();
    }

    void playExplosionSound() {
        explosionSound.setBuffer(soundLoader->getBuffer("../assets/sounds/Explosion.wav"));
        explosionSound.play();
    }

    void playLevelUpSound() {
        levelUpSound.setBuffer(soundLoader->getBuffer("../assets/sounds/LevelUp.wav"));
        levelUpSound.play();
    }

    void playExpPickupSound() {
        expPickupSound.setBuffer(soundLoader->getBuffer("../assets/sounds/ExpGemPickup.wav"));
        expPickupSound.play();
    }

    void playButtonClickSound() {
        buttonClickSound.setBuffer(soundLoader->getBuffer("../assets/sounds/ButtonClick.wav"));
        buttonClickSound.play();
    }

    void onNotify(const Event *event) override {
        switch (event->getEvType()) {
            case EventType::HPChanged: {
                const HPChanged* hpChangedEvent = dynamic_cast<const HPChanged*>(event);
                if (hpChangedEvent && hpChangedEvent->damageAmount > 0) {
                    playHitSound();
                }
                break;
            }
            case EventType::PlayerMoving:
                // Add moving sound logic here if needed
                break;

            case EventType::Pickup:
                playExpPickupSound();
                break;

            case EventType::Explosion:
                playExplosionSound();
                break;

            case EventType::LevelUp:
                playLevelUpSound();
                break;

            case EventType::ButtonClick:
                playButtonClickSound();
                break;

            default:
                break;
        }
    }
};

#endif
