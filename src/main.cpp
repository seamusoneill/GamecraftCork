#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <stdio.h>
#include "Box2D\Box2D.h"
#include <iostream>
#include "include/KeyboardManager.h"
#include <vector>
#include "include/ContactListener.h"
#include "include/CONSTANTS.h"
#include "include/Level.h"
#include "include/Player.h"
#include "include/AudioManager.h"
#include "LTimer.h"


Player* p;


//Program Variables
bool isRunning = true;
bool isMouseDown = false;

//Box2D Variables
b2World* m_world;
int32 velocityIterations = 8;
int32 positionIterations = 3;

//SDL Variables
SDL_Window* window;
SDL_Renderer* gRenderer;
SDL_Event e;

b2Vec2 mOffset;

SDL_Thread* threadToDrawEnemies;
SDL_Thread* threadToDrawPickups;
SDL_Thread* threadToDrawRest;

SDL_sem* dataLock = nullptr; // Will protect Renderer

Level lvl;

LTimer stepTimer;



//thread 2
int DrawLevelPickupsAndEnemies(void* data)
{
	while(true){
		 SDL_SemWait( dataLock );

		// Critical Section
		lvl.DrawEnemies(data);
		lvl.DrawPickups(data);
		// Critical Section
		SDL_RenderPresent((SDL_Renderer*)data);
		SDL_SemPost( dataLock );
	}

	return 0;
}

void DrawEntities(SDL_Renderer* r);

//thread 3
int DrawTheRest(void* data)
{
	while(true){
		 SDL_SemWait( dataLock );
		// Critical Section
		DrawEntities((SDL_Renderer*)data);
		// Critical Section

		SDL_SemPost( dataLock );	
	}

	return 0;
}

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
	SetupSDL();
	SetupWorld();
	lvl = Level();
	AudioManager::getInstance()->playBackgroundMusic();
	p = new Player(m_world, gRenderer, b2Vec2(200, 200), 40);
	lvl.Initialize(m_world, gRenderer,p);
	mOffset = b2Vec2(	(p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH / 2, 
						(p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT / 2);
	
	dataLock = SDL_CreateSemaphore( 1 );
	threadToDrawPickups =  SDL_CreateThread( DrawLevelPickupsAndEnemies, "PickupDrawThread", (void*)gRenderer);
	threadToDrawRest  =  SDL_CreateThread( DrawTheRest, "RestDrawThread", (void*)gRenderer);
}

void DrawEntities(SDL_Renderer* r) {

	lvl.Draw(r);
	p->Draw(r);
	
	for(int i = 0; i < p->cannonBalls.size();i++)
	{
		p->cannonBalls[i]->Draw(r, p->m_offset);
	}
}

void Quit() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(gRenderer);
	IMG_Quit();
	SDL_Quit();
	isRunning = false;

	SDL_DestroySemaphore( dataLock );
    dataLock = nullptr;
}

void Update() {
	
	//SDL_RenderClear( gRenderer );
	float timeStep = stepTimer.getTicks() / 1000.f;


	m_world->Step( (1 / 60.0f) * stepTimer.getTicks(), velocityIterations, positionIterations);


	mOffset = b2Vec2(	(p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH / 2, 
						(p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT / 2);

	if (p->GetPosition().x < -CONSTANTS::LEVEL_WIDTH/120)
	{
		mOffset.x = -CONSTANTS::LEVEL_WIDTH / 2;
	}
	if (p->GetPosition().x > CONSTANTS::LEVEL_WIDTH/120)
	{
		mOffset.x = -CONSTANTS::LEVEL_WIDTH / 60;
	}
	//Bottom Screen
	if (p->GetPosition().y < -CONSTANTS::LEVEL_HEIGHT/ 60 + 11.5)
	{
		mOffset.y = -CONSTANTS::LEVEL_HEIGHT / 5;
	}
	//Top screen
	if (p->GetPosition().y > CONSTANTS::LEVEL_HEIGHT / 60 - 11.5)
	{
		mOffset.y = CONSTANTS::LEVEL_HEIGHT / 2;
	}

	//b2Vec2 m_position = p->GetPosition();
	
	p->Update(mOffset,timeStep);
	lvl.Update(mOffset,timeStep);

	stepTimer.start();

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
	while (isRunning) {
		Update();
		
	}

	SDL_WaitThread( threadToDrawRest, nullptr );
	SDL_WaitThread( threadToDrawEnemies, nullptr );
	SDL_WaitThread( threadToDrawPickups, nullptr );
	return 0;
}