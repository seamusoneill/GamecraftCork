#ifndef HEALTHICON_H
#define HEALTHICON_H


#include "Box2D\Box2D.h"
#include "LTexture.h"

class HealthIcon {
public:
	HealthIcon();
	HealthIcon(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,  bool isHealth);
	~HealthIcon();
	void Draw(SDL_Renderer* renderer);

	bool GetIsHealth();
private:
	bool m_IsHealth;

	b2BodyDef myBodyDef;
	b2Body* m_Body;
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture mTexture;
};

#endif