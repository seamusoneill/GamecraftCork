#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "Enemy.h"

Enemy::Enemy(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius)
{
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	myBodyDef.userData = (void*)0;
	myBodyDef.angularDamping = 2;
	dynamicBody = world->CreateBody(&myBodyDef);
	circleShape.m_radius = radius * PIXELSTOMETRES;
	fixtureDef.shape = &circleShape;
	fixtureDef.filter.groupIndex = -1;
	fixtureDef.density = 0.1;
	dynamicBody->CreateFixture(&fixtureDef);

	texture.loadFromFile( "PirateShip.png", gRenderer );
}

void Enemy::Draw(SDL_Renderer* gRenderer, b2Vec2 offset)
{
	texture.render((dynamicBody->GetPosition().x * METRESTOPIXELS) - (texture.getWidth() / 2) - offset.x, 
		-(dynamicBody->GetPosition().y * METRESTOPIXELS) - (texture.getWidth() / 2) + offset.y, 
		NULL, dynamicBody->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );
}

void Enemy::Update(b2Vec2 playerPosition)
{
	float rotationAngle = TORADIANS*(atan2(-playerPosition.x, playerPosition.y));
	dynamicBody->SetTransform( dynamicBody->GetPosition(), rotationAngle );

	b2Vec2 m_velocity = playerPosition - dynamicBody->GetPosition();
	m_velocity.Normalize();
	m_velocity *= PIXELSTOMETRES * 75.00f;

	dynamicBody->SetLinearVelocity(m_velocity);
}

b2Vec2 Enemy::GetPosition()
{
	return b2Vec2(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);
}