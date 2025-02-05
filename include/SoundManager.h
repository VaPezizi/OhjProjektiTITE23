#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "raylib.h"
#include <unordered_map>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    void loadSound(const std::string& soundName, const char* fileName);
    void playSound(const std::string& soundName);
    void unloadSound(const std::string& soundName);
    void unloadAllSounds();

private:
    std::unordered_map<std::string, Sound> sounds;
};

#endif // SOUNDMANAGER_H