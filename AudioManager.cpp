#include "AudioManager.h"

AudioManager* AudioManager::me;

AudioManager* AudioManager::getAudioManager()
{
	if(me == NULL)
	{
		Mix_AllocateChannels(99999 );
		me = new AudioManager();
	}
	return me;
}

AudioManager::AudioManager(void)
{
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );


	backgroundMusic = Mix_LoadMUS("waves.wav");
}


AudioManager::~AudioManager(void)
{
}

void AudioManager::playBackgroundMusic(void){
	Mix_PlayMusic(backgroundMusic,-1);

}