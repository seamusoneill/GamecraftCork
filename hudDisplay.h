#ifndef HUDDISPLAY_H
#define HUDDISPLAY_H

#include "Box2D\Box2D.h"
#include "LTexture.h"

class hudDisplay {
public:
	hudDisplay();
	hudDisplay(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position);
	~hudDisplay();

	void Draw();
private:
	int m_health;
	int m_thurst;

	LTexture mHealthTexture;
	LTexture mThurstTexture;
};

#endif