#ifndef PLAYER_H
#define PLAYER_H

#include "Box2D/Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"
#include "CannonBall.h"
#include <vector>
#include <cmath>

class Player {
public:
	Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius);
	~Player();
	void Draw(SDL_Renderer* gRenderer, b2Vec2 offset);
	void Update();
	b2Vec2 GetPosition();

	b2Vec2 GetVelocity();
	int GetHealth();
	int GetThirst();
	void Collision();
	std::vector<CannonBall*> cannonBalls;

private:
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2Fixture* m_fixture;
	b2FixtureDef m_fixtureDef;
	LTexture m_texture;
	float m_angle;
	float m_speed;

	b2Vec2 m_velocity;
	int m_health;
	int m_ammo;
	int m_thirst;

	bool isAlive;
	bool isSpaceDown;

	void FireCannon();
	b2Timer timer;
	b2World* m_world;
	SDL_Renderer* gRenderer;
};

#endif
