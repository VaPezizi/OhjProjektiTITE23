#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager() {
    InitAudioDevice(); // Initialize audio device
}

SoundManager::~SoundManager() {
    unloadAllSounds();
    CloseAudioDevice(); // Close audio device
}

void SoundManager::loadSound(const std::string& soundName, const char* fileName) {
    sounds[soundName] = LoadSound(fileName); // Load sound
    if (sounds[soundName].stream.buffer == NULL) {
        std::cerr << "Failed to load sound: " << fileName << std::endl;
    } else {
        // sounds[soundName] is already stored in the map in the previous line
        std::cout << "Loaded sound: " << fileName << std::endl;
    }
}

void SoundManager::playSound(const std::string& soundName) {
    if (sounds.find(soundName) != sounds.end()) {
        PlaySound(sounds[soundName]); // Play sound
    }
}

void SoundManager::unloadSound(const std::string& soundName) {
    if (sounds.find(soundName) != sounds.end()) {
        UnloadSound(sounds[soundName]); // Unload sound
        sounds.erase(soundName);
    }
}

void SoundManager::unloadAllSounds() {
    for (auto& sound : sounds) {
        UnloadSound(sound.second); // Unload each sound
    }
    sounds.clear();
}
