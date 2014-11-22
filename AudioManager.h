#pragma once

#include <SDL_mixer.h>
class AudioManager
{
public:

	static AudioManager* me;
	static AudioManager* getAudioManager();
	AudioManager(void);
	~AudioManager(void);
	Mix_Music  *backgroundMusic;

	void AudioManager::playBackgroundMusic(void);
};

