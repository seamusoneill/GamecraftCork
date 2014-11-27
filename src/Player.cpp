#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "include/Player.h"
#include "include/AudioManager.h"


Player::Player(b2World* theWorld, SDL_Renderer* theRenderer, b2Vec2 position, float radius) : isSpaceDown(false), m_world(theWorld), gRenderer(theRenderer) {
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	m_bodyDef.userData = (void*)0;
	m_body = m_world->CreateBody(&m_bodyDef);
	m_shape.SetAsBox(radius / 2 * PIXELSTOMETRES, radius / 2 * PIXELSTOMETRES);
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_speed = .9;
	m_texture.loadFromFile("Player.png", gRenderer);
	m_health = 3;
	m_thirst = 60;
	isAlive = true;
}

void Player::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) {

		if(m_health<=0){
			//Remove the player Image from the game and replace it with the game over screen
				m_texture.loadFromFile("GameOver.png", gRenderer);
				m_texture.render(100,100,NULL, NULL,NULL, SDL_FLIP_NONE, gRenderer);
				isAlive = false;
		}
		else{
			m_texture.render((m_body->GetPosition().x * METRESTOPIXELS) - (m_texture.getWidth() / 2) - offset.x,
				-(m_body->GetPosition().y * METRESTOPIXELS) - (m_texture.getWidth() / 2) + offset.y,
				NULL, m_body->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer);
		}
}

void Player::Update() {

	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::D)) {
			m_body->SetAngularVelocity(-.9);
	}
	else if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::A)) {
			m_body->SetAngularVelocity(.9);
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

	 Collision();//check collision with pickups

	 if(thirstTimer.GetMilliseconds() > 1000)
	 {
		 m_thirst--;
		 thirstTimer.Reset();
	 }

	 if(m_thirst <= 0)
	 {
		 m_health = 0;
	 }
}

void Player::Collision(){
	if((int)m_body->GetUserData() == -200){
		if(m_health<3){
			m_health++;
		}
	}
	else if((int)m_body->GetUserData() == -400){
		if(m_thirst<3){
			m_thirst = 60;
		}
	}
	else if((int)m_body->GetUserData() == -100){
			m_health--;
		
	}

	m_body->SetUserData((void*)0);


}

b2Vec2 Player::GetPosition() {
	return b2Vec2(m_body->GetPosition().x, m_body->GetPosition().y);
}

b2Vec2 Player::GetVelocity() {
	return b2Vec2(m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y);
}

int Player::GetHealth(){
	return m_health;
}

int Player::GetThirst(){
	return m_thirst;
}

void Player::FireCannon()
{
	if(timer.GetMilliseconds() >500 && isAlive == true)
	{
		b2Vec2 direction = m_body->GetWorldVector(b2Vec2(0,1));
		cannonBalls.push_back(new CannonBall(m_world, gRenderer, m_body->GetPosition()+direction*2.5, 50, direction*10));
		timer.Reset();
		AudioManager::getInstance()->playCannon();
	}
				
}