#include "World.h"
#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)


World::World(){

}

void World::Initialize(b2World* w,SDL_Renderer* r){
	m_world = w;
	m_islands.push_back(new Island(30,-110,0,1,r,m_world));
}

World::~World(){}

void World::Update()
{
	for (int i = 0;i<m_islands.size();i++){
		m_islands.at(i)->Update();
	}
}

void World::Draw(SDL_Renderer* render, b2Vec2 offset){
	for (int i = 0;i<m_islands.size();i++){
		m_islands.at(i)->Draw(render, offset);
	}
}

Island::Island(float x, float y, int type, float scale,SDL_Renderer* r,b2World* w)
{
	if (type == 0){
		m_texture.loadFromFile("Island.png", r);
		m_sizeX = 51;
		m_sizeY = 28;
	}
	m_scale = scale;
	m_posX = x;
	m_posY = y;

	b2BodyDef		l_bodyDef;
	b2PolygonShape	l_squareShape;
	b2FixtureDef	l_fixtureDef;

	l_bodyDef.type = b2_staticBody;
	l_bodyDef.position = b2Vec2(x * PIXELSTOMETRES,y *PIXELSTOMETRES);
	m_body = w->CreateBody(&l_bodyDef);

	l_squareShape.SetAsBox(m_sizeX*m_scale,m_sizeY*m_scale);
	l_fixtureDef.shape = &l_squareShape;
	m_body->CreateFixture(&l_fixtureDef);
}
Island::~Island()
{}
void Island::Update(){}

void Island::Draw(SDL_Renderer* renderer,b2Vec2 offset){
	m_texture.render(m_posX- (m_texture.getWidth() / 2) - offset.x,-m_posY - (m_texture.getHeight() / 2) + offset.y, NULL,NULL , NULL, SDL_FLIP_NONE, renderer );
}