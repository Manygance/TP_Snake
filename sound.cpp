#include "sound.hpp"
#include <fmod/fmod_errors.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

SoundManager::SoundManager() : system(nullptr), backgroundMusic(nullptr), musicChannel(nullptr) {
    std::srand(std::time(nullptr)); // Initialize random seed
}

SoundManager::~SoundManager() {
    if (backgroundMusic) {
        FMOD_Sound_Release(backgroundMusic);
    }
    if (system) {
        FMOD_System_Close(system);
        FMOD_System_Release(system);
    }
}

bool SoundManager::initialize() {
    FMOD_RESULT result = FMOD_System_Create(&system);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    result = FMOD_System_Init(system, 512, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    return true;
}

void SoundManager::update() {
    FMOD_System_Update(system);
}

void SoundManager::playBackgroundMusic(const std::string& filePath) {
    if (backgroundMusic) {
        FMOD_Sound_Release(backgroundMusic);
    }

    FMOD_RESULT result = FMOD_System_CreateSound(system, filePath.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, nullptr, &backgroundMusic);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, backgroundMusic, false, &musicChannel);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
    }
}

void SoundManager::stopBackgroundMusic() {
    if (musicChannel) {
        FMOD_Channel_Stop(musicChannel);
    }
    if (backgroundMusic) {
        FMOD_Sound_Release(backgroundMusic);
        backgroundMusic = nullptr;
    }
}

void SoundManager::playRandomMusic(const std::vector<std::string>& filePaths) {
    if (filePaths.empty()) {
        std::cerr << "No music files provided" << std::endl;
        return;
    }

    int randomIndex = std::rand() % filePaths.size();
    playBackgroundMusic(filePaths[randomIndex]);
}

void SoundManager::playSoundEffect(const std::string& filePath) {
    FMOD_SOUND *soundEffect;
    FMOD_RESULT result = FMOD_System_CreateSound(system, filePath.c_str(), FMOD_DEFAULT, nullptr, &soundEffect);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, soundEffect, false, &musicChannel);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
    }

    FMOD_Sound_Release(soundEffect);
}

void SoundManager::setBackgroundMusicVolume(float volume) {
    if (musicChannel) {
        FMOD_Channel_SetVolume(musicChannel, volume);
        cout<<"Volume set to "<<volume<<endl;
    }
    else
    {
        cout<<"No music channel"<<endl;
    }
}
