#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30

#include <SDL.h>
#include <SDL_image.h>
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

//SDL Variables
SDL_Window* window;
SDL_Renderer* gRenderer;
SDL_Event e;



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
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	
	lvl->Draw(gRenderer, offset);
	p->Draw(gRenderer, offset);
	
	for(int i = 0; i < p->cannonBalls.size();i++)
	{
		p->cannonBalls[i]->Draw(gRenderer, offset);
	}
	
	SDL_RenderPresent(gRenderer);
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
	
	
	b2Vec2 offset = b2Vec2((p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH / 2, (p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT / 2);

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

	while (isRunning) Update();
	return 0;
}