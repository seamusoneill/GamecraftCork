#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "PickUp.h"

PickUp::PickUp(){
}
PickUp::PickUp(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,  bool isWater){
	m_IsWater = isWater;

	if (m_IsWater){
		mTexture.loadFromFile( "WaterBucket.png", gRenderer );
	}
	else{
		mTexture.loadFromFile( "Wiskey.png", gRenderer );
	}
	m_alive = true;
	m_value = 0.5f;

	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(position.x*PIXELSTOMETRES, -position.y*PIXELSTOMETRES);
	myBodyDef.userData = (void*)-2;
	m_Body = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(mTexture.getWidth()/2*PIXELSTOMETRES, mTexture.getHeight()/2*PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	m_Body->CreateFixture(&fixtureDef);
}

void PickUp::Draw(SDL_Renderer* renderer, b2Vec2 offset){
	if (m_alive == true){
	mTexture.render((m_Body->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
		-(m_Body->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL,NULL , NULL, SDL_FLIP_NONE, renderer );
	}
}


void PickUp::Collected(b2World* world){
	if(myBodyDef.userData == (void*)-100){
	m_alive = false;
	world->DestroyBody(m_Body);
	}
}

bool PickUp::GetIsWater(){
	return m_IsWater;
}
float PickUp::GetValue(){
	return m_value;
}