#ifndef ENEMY_H
#define ENEMY_H

#include "Box2D/Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"
#include "CannonBall.h"
#include <vector>

class Enemy
{
public:
	Enemy(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius);
	~Enemy();
	void Draw(SDL_Renderer* gRenderer, b2Vec2 offset );
	void Update(b2Vec2 playerPosition,b2Vec2 playerVelocity);
	b2Vec2 GetPosition();
	bool GetAlive();
	std::vector<CannonBall*> cannonBalls;

private:
	b2World* mWorld;


	b2BodyDef myBodyDef;
	b2Body* dynamicBody;
	b2CircleShape circleShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;

	LTexture texture;
	LTexture deadTexture;

	b2Vec2 orientation;
	b2Timer timer;
	b2World* m_world;
	SDL_Renderer* gRenderer;
	bool m_alive;
};

#endif
