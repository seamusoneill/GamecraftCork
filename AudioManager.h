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




	Mix_Chunk *cannon;
	Mix_Chunk *crack;
	Mix_Chunk *pickup;




	void playCannon(void);
	void playCrack(void);
	void playPickup(void);




	void AudioManager::playBackgroundMusic(void);
};

