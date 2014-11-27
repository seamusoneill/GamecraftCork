#ifndef HUDDISPLAY_H
#define HUDDISPLAY_H

#include "Box2D\Box2D.h"
#include "LTexture.h"

#include "HealthIcon.h"

class HudDisplay {
public:
	HudDisplay();
	HudDisplay(b2World* world, SDL_Renderer* gRenderer, b2Vec2* healthPosition, b2Vec2* thirstPosition,const int healthArraySize,const int thirstArraySize);
	~HudDisplay();

	void Draw(SDL_Renderer* renderer,int health, int thirst);

	void UpdateHealth();
	void UpdateThurst();
private:
	int m_health;
	int m_thurst;

	HealthIcon *Health[3];
	HealthIcon *Thirst[3];


	LTexture mHealthTexture;
	LTexture mThurstTexture;

};

#endif