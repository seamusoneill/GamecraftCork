#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "HealthIcon.h"

HealthIcon::HealthIcon(){}
HealthIcon::HealthIcon(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,  bool isHealth){
	m_IsHealth = isHealth;

	if (m_IsHealth){
		mTexture.loadFromFile( "Heart.png", gRenderer );
	}
	else{
		mTexture.loadFromFile( "Drop.png", gRenderer );
	}


	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(position.x*PIXELSTOMETRES, -position.y*PIXELSTOMETRES);
	myBodyDef.userData = (void*)-2;
	m_Body = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(mTexture.getWidth()/2*PIXELSTOMETRES, mTexture.getHeight()/2*PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	m_Body->CreateFixture(&fixtureDef);
}
HealthIcon::~HealthIcon(){}
void HealthIcon::Draw(SDL_Renderer* renderer){
	mTexture.render((m_Body->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) ,
		-(m_Body->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) , NULL,NULL , NULL, SDL_FLIP_NONE, renderer );
}


bool HealthIcon::GetIsHealth(){
	return m_IsHealth;
}




