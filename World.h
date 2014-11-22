# pragma once	

#include <SDL.h>
#include <vector>
#include <Box2D\Box2D.h>
#include "LTexture.h"
using namespace std;

class Island{
	private:
		int m_type;
		LTexture m_texture;
		b2Body*	m_body; 
		float m_sizeX,m_sizeY,m_posX,m_posY,m_scale;

	public:
		Island(float x, float y, int type, float scale,SDL_Renderer* r, b2World*); // 0 is water island
		~Island();

		void Update();

		void Draw(SDL_Renderer*,b2Vec2 offset);
};

class World{
private:
	vector<Island*> m_islands;
	b2World* m_world;

public:
	World();
	~World();
	void Initialize(b2World*,SDL_Renderer* r);
	void Update();

	void Draw(SDL_Renderer*, b2Vec2 offset);
}; 


