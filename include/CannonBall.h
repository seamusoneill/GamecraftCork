#ifndef CANNONBALL_H
#define CANNONBALL_H

#include "Box2D/Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"
class CannonBall
{
public:

	CannonBall(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius,b2Vec2 direction);
	~CannonBall();
	void Draw(SDL_Renderer* gRenderer, b2Vec2 offset );
	b2Vec2 GetPosition();

private:
	b2BodyDef myBodyDef;
	b2Body* dynamicBody;
	b2CircleShape circleShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture texture;
	b2Vec2 orientation;
};

#endif
