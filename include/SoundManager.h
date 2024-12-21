#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include "GUI/Observer.h"
#include <SFML/Audio.hpp>
#include "GUI/Events.h"

class SoundManager : public Observer {
private:
    sf::Clock movingSoundCooldownClock;
    sf::Time movingSoundCooldown = sf::milliseconds(200); // Minimum interval

    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::SoundBuffer levelUpBuffer;
    sf::SoundBuffer playerMovingpBuffer;
    sf::SoundBuffer expPickupBuffer;

    sf::Sound hitSound;
    sf::Sound explosionSound;
    sf::Sound levelUpSound;
    sf::Sound playerMovingSound;
    sf::Sound expPickupSound;

    sf::Music backgroundMusic; // Use sf::Music for background music
    std::vector<std::string> playlist; // Playlist of music tracks
    int currentTrackIndex = 0; // Track currently playing

public:
    SoundManager() {
        if (!hitBuffer.loadFromFile("../assets/sounds/Hit1.wav")) {
            std::cerr << "Error loading Hit1.wav" << std::endl;
        }
        if (!explosionBuffer.loadFromFile("../assets/sounds/Explosion.wav")) {
            std::cerr << "Error loading Explosion.wav" << std::endl;
        }
        if (!levelUpBuffer.loadFromFile("../assets/sounds/LevelUp.wav")) {
            std::cerr << "Error loading LevelUp.wav" << std::endl;
        }
        if (!expPickupBuffer.loadFromFile("../assets/sounds/ExpGemPickup.wav")) {
            std::cerr << "Error loading ExpGemPickup.wav" << std::endl;
        }
        if (!playerMovingpBuffer.loadFromFile("../assets/sounds/PlayerMoving.wav")) {
            std::cerr << "Error loading PlayerMoving.wav" << std::endl;
        }

        hitSound.setBuffer(hitBuffer);
        explosionSound.setBuffer(explosionBuffer);
        levelUpSound.setBuffer(levelUpBuffer);
        playerMovingSound.setBuffer(playerMovingpBuffer);
        expPickupSound.setBuffer(expPickupBuffer);


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
    
    void onNotify(const Event *event) override {
        switch (event->getEvType()) {
            case EventType::HPChanged: {
                const HPChanged* hpChangedEvent = dynamic_cast<const HPChanged*>(event);
                if (hpChangedEvent && hpChangedEvent->damageAmount > 0) {
                    hitSound.play();
                }
                break;
            }
            
            case EventType::PlayerMoving:
               if (movingSoundCooldownClock.getElapsedTime() > movingSoundCooldown) {
                    //playerMovingSound.play();
                    movingSoundCooldownClock.restart();
                }
                break;

            case EventType::Pickup:
                expPickupSound.play();
                break;

            case EventType::Explosion:
                explosionSound.play();
                break;

            case EventType::LevelUp:
                levelUpSound.play();
                break;

            default:
                break;
        }
    }
};


#endif