#ifndef PICKUP_H
#define PICKUP_H


#include "Box2D\Box2D.h"
#include "LTexture.h"

class PickUp {
public:
	PickUp();
	PickUp(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,  bool isWater);
	~PickUp();
	void Draw(SDL_Renderer* renderer);
	void Update( b2Vec2 offset);

	bool GetIsWater();
	float GetValue();
private:
	b2Vec2 m_offset;
	b2BodyDef myBodyDef;
	b2Body* m_Body;
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture mTexture;

	float m_value; //the value that the pickup will add to the health or thirst
	bool m_IsWater; // if this varible is true the varible is water, otherwise it is alcohol (i.e. health)
	bool m_alive; //if this is true draw the texture and update the body
};

#endif