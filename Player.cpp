#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "Player.h"

Player::Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius) : isSpaceDown(false) {
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.userData = (void*)0;
	m_body = world->CreateBody(&m_bodyDef);
	m_shape.SetAsBox(radius / 2 * PIXELSTOMETRES, radius / 2 * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_fixtureDef.filter.groupIndex = -1;
	m_body->CreateFixture(&m_fixtureDef);
	m_speed = .3;
	m_texture.loadFromFile("Player.png", gRenderer);
}

void Player::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) {
	m_texture.render((m_body->GetPosition().x * METRESTOPIXELS) - (m_texture.getWidth() / 2) - offset.x,
		-(m_body->GetPosition().y * METRESTOPIXELS) - (m_texture.getWidth() / 2) + offset.y,
		NULL, m_body->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer);
}

void Player::Update() {
	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::D)) {
			m_body->SetAngularVelocity(-.2);
	}
	else if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::A)) {
			m_body->SetAngularVelocity(.2);
	}
	else{
		m_body->SetAngularVelocity(0);
	}
	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::W)) {
		m_angle = m_body->GetAngle();

		m_velocity.x = ((float)sin(m_angle) * -m_speed);
		m_velocity.y = ((float)cos(m_angle) * m_speed);

		m_body->ApplyForceToCenter(m_velocity, true);
	}
	else if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::S)) {
		m_angle = m_body->GetAngle();

		m_velocity.x = ((float)sin(m_angle) * m_speed);
		m_velocity.y = ((float)cos(m_angle) * -m_speed);

		m_body->ApplyForceToCenter(m_velocity, true);
	}
	else
	{
		m_body->SetLinearVelocity(b2Vec2(0,0));
	}
	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::SPACE))
	{
		FireCannon();
		isSpaceDown = true;
	}
	else { isSpaceDown = false; }
}

b2Vec2 Player::GetPosition() {
	return b2Vec2(m_body->GetPosition().x, m_body->GetPosition().y);
}

int Player::GetHealth(){
	return m_health;
}

int Player::GetThirst(){
	return m_thirst;
}

void Player::FireCannon()
{
}