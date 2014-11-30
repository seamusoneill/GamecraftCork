#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "PickUp.h"
#include "Player.h"
#include "Enemy.h"
#include "Island.h"
#include "CONSTANTS.h"
#include <vector>


class Level{
private:
	Player* m_player;
	std::vector<PickUp*> m_pickups;
	std::vector<Enemy*> m_enemies;
	Island* m_island;
	LTexture m_background;
	b2Vec2 m_offset; // Drawing one.  Changes when player moves.
	float m_timeStep;

public:
	Level();

	void Initialize(b2World*, SDL_Renderer*, Player*);
	void Update( b2Vec2 offset,float timeStep);
	void Draw(SDL_Renderer*);

	int DrawEnemies(void* rendererData);
	int DrawPickups(void* rendererData);

};

#endif