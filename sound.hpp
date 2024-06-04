#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>
#include <vector>
#include <fmod/fmod.h>

extern FMOD_SYSTEM *player;
extern FMOD_SOUND *backgroundMusic;
extern FMOD_CHANNEL *musicChannel;

bool initializeSoundSystem();
void updateSoundSystem();
void playBackgroundMusic(const std::string& filePath);
void stopBackgroundMusic();
void playSoundEffect(const std::string& filePath);
void setBackgroundMusicVolume(float volume);
void cleanupSoundSystem();

#endif // SOUND_HPP