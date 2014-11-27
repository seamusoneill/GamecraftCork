#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "include/Enemy.h"
#include "include/AudioManager.h"

Enemy::Enemy(b2World* theWorld, SDL_Renderer* theRenderer, b2Vec2 position, float radius) : m_world(theWorld), gRenderer(theRenderer)
{
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	myBodyDef.userData = (void*)-1;
	myBodyDef.angularDamping = 2;

	dynamicBody = m_world->CreateBody(&myBodyDef);
	circleShape.m_radius = radius * PIXELSTOMETRES;

	fixtureDef.shape = &circleShape;
	fixtureDef.filter.groupIndex = 0;
	fixtureDef.density = 0.1;
	dynamicBody->CreateFixture(&fixtureDef);
	m_alive = true;
	texture.loadFromFile( "PirateShip.png", gRenderer );
}

void Enemy::Draw(SDL_Renderer* gRenderer, b2Vec2 offset)
{
	texture.render((dynamicBody->GetPosition().x * METRESTOPIXELS) - (texture.getWidth() / 2) - offset.x, 
		-(dynamicBody->GetPosition().y * METRESTOPIXELS) - (texture.getWidth() / 2) + offset.y, 
		NULL, dynamicBody->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );
}

void Enemy::Update(b2Vec2 playerPosition,b2Vec2 playerVelocity)
{
	int fireRadius = 10;
	//int fireRadius = rand() % 4+5;

	float rotationAngle = (atan2(-playerPosition.x, playerPosition.y));

	b2Vec2 diff;
	diff.x = playerVelocity.x - dynamicBody->GetLinearVelocity().x;
	diff.y = playerVelocity.y - dynamicBody->GetLinearVelocity().y;

	float turnAngle = atan2(diff.x, diff.y) * 3.14/180;

	if( b2Distance(playerPosition, dynamicBody->GetPosition()) > fireRadius)
	{
		dynamicBody->SetTransform( dynamicBody->GetPosition(), rotationAngle );
		
		//dynamicBody->SetAngularVelocity(turnAngle);
		//dynamicBody->SetTransform(dynamicBody->GetPosition(),turnAngle);

		b2Vec2 m_velocity = playerPosition - dynamicBody->GetPosition();
		m_velocity.Normalize();
		m_velocity *= PIXELSTOMETRES * 75.00f;

		dynamicBody->SetLinearVelocity(m_velocity*0.5);
		timer.Reset();
	}
	else
	{
		dynamicBody->SetLinearVelocity(b2Vec2(0,0));
		dynamicBody->SetTransform( dynamicBody->GetPosition(), rotationAngle+90 );

		if(timer.GetMilliseconds() >3000)
		{
			b2Vec2 direction = playerPosition - dynamicBody->GetPosition();
			direction.Normalize();
			direction *= PIXELSTOMETRES * 750.0f;

			AudioManager::getInstance()->playCannon();
			direction = dynamicBody->GetWorldVector(b2Vec2(1,0));
			cannonBalls.push_back(new CannonBall(m_world, gRenderer, dynamicBody->GetPosition()+direction*2.5, 50, direction*10));
			timer.Reset();
		}
	}

	if((int)dynamicBody->GetUserData() == -100)
	{
		m_alive = false;
	}
}

b2Vec2 Enemy::GetPosition()
{
	return b2Vec2(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);
}

bool Enemy::GetAlive()
{
	return m_alive;
}