#ifndef PICKUP_H
#define PICKUP_H


#include "Box2D\Box2D.h"
#include "LTexture.h"

class Pickup {
public:
	Pickup();
	Pickup(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float angleRadians, bool isWater);
	~Pickup();
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
private:
		
	b2BodyDef myBodyDef;
	b2Body* staticBody;
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture mTexture;

	float m_value;
	bool m_IsWater;
};

#endif