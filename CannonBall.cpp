#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "CannonBall.h"

CannonBall::CannonBall(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius, b2Vec2 direction)
{
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(position.x, position.y);
	myBodyDef.userData = (void*)0;
	myBodyDef.angularDamping = 2;
	dynamicBody = world->CreateBody(&myBodyDef);
	circleShape.m_radius = radius * PIXELSTOMETRES;
	fixtureDef.shape = &circleShape;
	fixtureDef.filter.groupIndex = -1;
	fixtureDef.density = 0.1;
	dynamicBody->CreateFixture(&fixtureDef);

	dynamicBody->SetLinearVelocity(direction);

	texture.loadFromFile( "CannonBall.png", gRenderer );
}

void CannonBall::Draw(SDL_Renderer* gRenderer, b2Vec2 offset)
{
	texture.render((dynamicBody->GetPosition().x * METRESTOPIXELS) - (texture.getWidth() / 2) - offset.x, 
		-(dynamicBody->GetPosition().y * METRESTOPIXELS) - (texture.getWidth() / 2) + offset.y, 
		NULL, dynamicBody->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );
}

b2Vec2 CannonBall::GetPosition()
{
	return b2Vec2(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);
}