#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <string>
#include <stdio.h>
#include "Box2D\Box2D.h"
#include <iostream>
#include "KeyboardManager.h"
#include <vector>
#include "ContactListener.h"
#include "CONSTANTS.h"
#include "Level.h"
#include "Player.h"
#include "AudioManager.h"
Player* p;

Level* lvl;

//Program Variables
bool isRunning = true;
bool isMouseDown = false;

//Box2D Variables
b2World* m_world;
int32 velocityIterations = 8;
int32 positionIterations = 3;
b2Vec2 offset;

//SDL Variables
SDL_Window* window;
SDL_Renderer* gRenderer;
SDL_Event e;

SDL_sem* gDataLock = NULL;
int gData = -1;
int worker( void* data );
int threadFunction( void* data );
void close();

void SetupWorld() {
	b2Vec2 gravity(0, 0);
	m_world = new b2World(gravity);
	m_world->SetContactListener(ContactListener::getListener());
}

void SetupSDL() {
	window = SDL_CreateWindow("Treasure Flood", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	IMG_Init(IMG_INIT_PNG);
}

void Initialize()
{
	SetupWorld();
	SetupSDL();
	lvl = new Level();
	AudioManager::getAudioManager()->playBackgroundMusic();
	p = new Player(m_world, gRenderer, b2Vec2(0, 0), 40);
	lvl->Initialize(m_world, gRenderer,p);
}

void DrawEntities(b2Vec2 offset) {
	//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//SDL_RenderClear( gRenderer );

	
	//lvl->Draw(gRenderer, offset);
	//p->Draw(gRenderer, offset);
	
	//for(int i = 0; i < p->cannonBalls.size();i++)
	//{
	//	p->cannonBalls[i]->Draw(gRenderer, offset);
	//}
	
	//SDL_RenderPresent(gRenderer);
}

void Quit() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(gRenderer);
	IMG_Quit();
	SDL_Quit();
	isRunning = false;
}

void Update() {
	m_world->Step(1 / 30.0f, velocityIterations, positionIterations);
	
	
	offset = b2Vec2((p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH / 2, (p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT / 2);

	if (p->GetPosition().x < -CONSTANTS::LEVEL_WIDTH/120)
	{
		offset.x = -CONSTANTS::LEVEL_WIDTH / 2;
	}
	if (p->GetPosition().x > CONSTANTS::LEVEL_WIDTH/120)
	{
		offset.x = -CONSTANTS::LEVEL_WIDTH / 60;
	}
	//Bottom Screen
	if (p->GetPosition().y < -CONSTANTS::LEVEL_HEIGHT/ 60 + 11.5)
	{
		offset.y = -CONSTANTS::LEVEL_HEIGHT / 5;
	}
	//Top screen
	if (p->GetPosition().y > CONSTANTS::LEVEL_HEIGHT / 60 - 11.5)
	{
		offset.y = CONSTANTS::LEVEL_HEIGHT / 2;
	}
	b2Vec2 m_position = p->GetPosition();
	DrawEntities(offset);
	p->Update();
	lvl->Update();

	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::ESC))
		Quit();

	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::MOUSE)) {
		if (!isMouseDown) {
		}
		isMouseDown = true;
	}
	else { isMouseDown = false; }
}

int main(int argc, char* args[]) {
	Initialize();

	//Run the thread
    int data = 101;
    //SDL_Thread* threadID = SDL_CreateThread( threadFunction, "ThreadA", (void*)data );
	SDL_Thread* threadA = SDL_CreateThread( worker, "Thread A", (void*)"Thread A" );
	SDL_Delay( 16 + rand() % 32 );
	SDL_Thread* threadB = SDL_CreateThread( worker, "Thread B", (void*)"Thread B" );

	while( isRunning )
	{
		Update();
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		//SDL_RenderClear( gRenderer );
		p->Draw(gRenderer, offset);
		for(int i = 0; i < p->cannonBalls.size();i++)
		{
			p->cannonBalls[i]->Draw(gRenderer, offset);
		}
		SDL_RenderPresent( gRenderer );
	}

    //Remove timer in case the call back was not called
    //SDL_WaitThread( threadID, NULL );
	SDL_WaitThread( threadA, NULL );
	SDL_WaitThread( threadB, NULL );

	return 0;
}

int threadFunction( void* data )
{
	while( isRunning )
	{
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		lvl->Draw(gRenderer, offset);
		SDL_RenderPresent( gRenderer );
	}
    return 0;
}

void close()
{
	//Free semaphore
	SDL_DestroySemaphore( gDataLock );
	gDataLock = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	//SDL_DestroyWindow( gWindow );
	//gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int worker( void* data )
{
	//Pre thread random seeding
	srand( SDL_GetTicks() );
	
	//Work 5 times
	//for( int i = 0; i < 5; ++i )
	//{
	while( isRunning )
	{
		//Wait randomly
		SDL_Delay( 16 + rand() % 32 );
		
		//Lock
		SDL_SemWait( gDataLock );

		//"Work"
		gData = rand() % 256;

		//Unlock
		SDL_SemPost( gDataLock );

		//Wait randomly
		SDL_Delay( 16 + rand() % 640 );
		
		while( isRunning )
		{
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			lvl->Draw(gRenderer, offset);
			SDL_RenderPresent( gRenderer );
		}
	}
	return 0;
}
