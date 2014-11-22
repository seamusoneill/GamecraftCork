#ifndef PLAYER_H
#define PLAYER_H

#include "Box2D/Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"
class Player {
public:
	Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius);
	~Player();
	void Draw(SDL_Renderer* gRenderer, b2Vec2 offset);
	void Update();
	b2Vec2 GetPosition();

private:
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2Fixture* m_fixture;
	b2FixtureDef m_fixtureDef;
	LTexture m_texture;

	int m_health;
	int m_ammo;
	int m_thirst;

	bool isAlive;
	bool isSpaceDown;
};

#endif