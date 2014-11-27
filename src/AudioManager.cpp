#include "include/AudioManager.h"

AudioManager* AudioManager::mInstance;

AudioManager* AudioManager::getInstance()
{
	if(mInstance == NULL)
	{
		Mix_AllocateChannels(99999 );
		mInstance = new AudioManager();
	}
	return mInstance;
}

AudioManager::AudioManager(void)
{
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	cannon = Mix_LoadWAV("cannon.wav");
	crack = Mix_LoadWAV("crack.wav");
	pickup = Mix_LoadWAV("pickup.wav");
	backgroundMusic = Mix_LoadMUS("waves.wav");
}

AudioManager::~AudioManager(void)
{}

void AudioManager::playBackgroundMusic(void){
	Mix_PlayMusic(backgroundMusic,-1);
}

void AudioManager::playCannon(void){
	Mix_PlayChannel( -1, cannon, 0 );
}
void AudioManager::playCrack(void){
	Mix_PlayChannel( -1, crack, 0 );
}
void AudioManager::playPickup(void){
	Mix_PlayChannel( -1, pickup, 0 );
}