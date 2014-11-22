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

	m_texture.loadFromFile("Player.png", gRenderer);
}

void Player::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) {
	m_texture.render((m_body->GetPosition().x * METRESTOPIXELS) - (m_texture.getWidth() / 2) - offset.x,
		-(m_body->GetPosition().y * METRESTOPIXELS) - (m_texture.getWidth() / 2) + offset.y,
		NULL, m_body->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer);
}

void Player::Update() {
	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::D)) {
		if (m_body->GetContactList()) {
			m_body->ApplyForceToCenter(b2Vec2(10, 0), true);
		}
		else {
			m_body->ApplyForceToCenter(b2Vec2(5, 0), true);
		}
	}
	else if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::A)) {
		if (m_body->GetContactList()) {
			m_body->SetLinearVelocity(b2Vec2(-10, m_body->GetLinearVelocity().y));
		}
		else {
			m_body->ApplyForceToCenter(b2Vec2(-5, 0), true);
		}
	}
	else if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::W)) {
		if (m_body->GetContactList()) {
			m_body->ApplyForceToCenter(b2Vec2(0, 10), true);
		}
		else {
			m_body->ApplyForceToCenter(b2Vec2(-5, 0), true);
		}
	}
	else if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::S)) {
		if (m_body->GetContactList()) {
			m_body->ApplyForceToCenter(b2Vec2(0,-10), true);
		}
		else {
			m_body->ApplyForceToCenter(b2Vec2(-5, 0), true);
		}
	}

	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::SPACE)) {
		if (m_body->GetContactList() && !isSpaceDown) {
			m_body->ApplyLinearImpulse(b2Vec2(0, 12.5), m_body->GetPosition(), true);
			isSpaceDown = true;
		}
	}
	else { isSpaceDown = false; }
}

b2Vec2 Player::GetPosition() {
	return b2Vec2(m_body->GetPosition().x, m_body->GetPosition().y);
}