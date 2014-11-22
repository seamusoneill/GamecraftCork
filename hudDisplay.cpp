#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "hudDisplay.h"

HudDisplay::HudDisplay(){}
HudDisplay::HudDisplay(b2World* world, SDL_Renderer* gRenderer, b2Vec2* healthPosition, b2Vec2* thirstPosition, int const healthArraySize, int const thirstArraySize){
	
	Health[healthArraySize];
	Thirst[thirstArraySize];

	for(int i = 0; i <healthArraySize;i++){

		//	HealthIcon(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,  bool isHealth);
	Health[i] = new HealthIcon(world, gRenderer, b2Vec2(healthPosition->x*i,healthPosition->y),true);
	}

	for(int i = 0; i <thirstArraySize;i++){
	Thirst[i] = new HealthIcon(world, gRenderer, b2Vec2(thirstPosition->x*i,thirstPosition->y), false);
	}

}
HudDisplay::~HudDisplay(){

}

void HudDisplay::Draw(SDL_Renderer* renderer,int health, int thirst){
	for(int i = 0; i < health; i++){//only draw as much health as the player has
	Health[i]->Draw(renderer);
	}

	for(int i = 0; i < thirst; i++){//only draw as much thirst as the player has
	Thirst[i]->Draw(renderer);
	}
}