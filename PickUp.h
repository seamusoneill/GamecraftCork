#ifndef PICKUP_H
#define PICKUP_H


#include "Box2D\Box2D.h"
#include "LTexture.h"

class Pickup {
public:
	Pickup();
	Pickup(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,  bool isWater);
	~Pickup();
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	void Collected(b2World* world);
private:
		
	b2BodyDef myBodyDef;
	b2Body* m_Body;
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture mTexture;

	float m_value;
	bool m_IsWater;
	bool m_alive;
};

#endif