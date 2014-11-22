#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "PickUp.h"

Pickup::Pickup(){
}
Pickup::Pickup(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,  bool isWater){
	m_IsWater = isWater;

	if (m_IsWater){
		mTexture.loadFromFile( "WaterBucket.png", gRenderer );
	}
	else{
		mTexture.loadFromFile( "Wiskey.png", gRenderer );
	}

	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(position.x*PIXELSTOMETRES, -position.y*PIXELSTOMETRES);
	myBodyDef.userData = (void*)-2;
	staticBody = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(mTexture.getWidth()/2*PIXELSTOMETRES, mTexture.getHeight()/2*PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	staticBody->CreateFixture(&fixtureDef);
}

void Pickup::Draw(SDL_Renderer* renderer, b2Vec2 offset){
	mTexture.render((staticBody->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
		-(staticBody->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL,NULL , NULL, SDL_FLIP_NONE, renderer );
}