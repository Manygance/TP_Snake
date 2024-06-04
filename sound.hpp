#ifndef MEDIAPLAYER_HPP
#define MEDIAPLAYER_HPP

#include <fmod/fmod.hpp>
#include <vector>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    bool initialize();
    void update();

    void playBackgroundMusic(const std::string& filePath);
    void stopBackgroundMusic();
    void playRandomMusic(const std::vector<std::string>& filePaths);
    void playSoundEffect(const std::string& filePath);
    void setBackgroundMusicVolume(float volume);

    static SoundManager& getInstance() {
        static SoundManager instance;
        return instance;
    }

private:
    FMOD_SYSTEM *system;
    FMOD_SOUND *backgroundMusic;
    FMOD_CHANNEL *musicChannel;
};


#endif // MEDIAPLAYER_HPP