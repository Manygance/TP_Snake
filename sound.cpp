#include "sound.hpp"
#include <fmod/fmod_errors.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

FMOD_SYSTEM *player = nullptr;
FMOD_SOUND *backgroundMusic = nullptr;
FMOD_CHANNEL *musicChannel = nullptr;

bool initializeSoundSystem() {
    std::srand(std::time(nullptr)); // Initialize random seed

    FMOD_RESULT result = FMOD_System_Create(&player);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    result = FMOD_System_Init(player, 512, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
        return false;
    }

    return true;
}

void updateSoundSystem() {
    FMOD_System_Update(player);
}

void playBackgroundMusic(const std::string& filePath) {
    if (backgroundMusic) {
        FMOD_Sound_Release(backgroundMusic);
    }

    FMOD_RESULT result = FMOD_System_CreateSound(player, filePath.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, nullptr, &backgroundMusic);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    result = FMOD_System_PlaySound(player, FMOD_CHANNEL_FREE, backgroundMusic, false, &musicChannel);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
    }
}

void stopBackgroundMusic() {
    if (musicChannel) {
        FMOD_Channel_Stop(musicChannel);
    }
    if (backgroundMusic) {
        FMOD_Sound_Release(backgroundMusic);
        backgroundMusic = nullptr;
    }
}

void playSoundEffect(const std::string& filePath) {
    FMOD_SOUND *soundEffect;
    FMOD_RESULT result = FMOD_System_CreateSound(player, filePath.c_str(), FMOD_DEFAULT, nullptr, &soundEffect);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
        return;
    }

    result = FMOD_System_PlaySound(player, FMOD_CHANNEL_FREE, soundEffect, false, &musicChannel);
    if (result != FMOD_OK) {
        std::cerr << "FMOD error: " << FMOD_ErrorString(result) << std::endl;
    }

    FMOD_Sound_Release(soundEffect);
}

void setBackgroundMusicVolume(float volume) {
    if (musicChannel) {
        FMOD_Channel_SetVolume(musicChannel, volume);
        std::cout << "Volume set to " << volume << std::endl;
    } else {
        std::cout << "No music channel" << std::endl;
    }
}

void cleanupSoundSystem() {
    if (backgroundMusic) {
        FMOD_Sound_Release(backgroundMusic);
    }
    if (player) {
        FMOD_System_Close(player);
        FMOD_System_Release(player);
    }
}
