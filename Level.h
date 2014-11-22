#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "PickUp.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Level{
private:
	Player* m_player;
	std::vector<PickUp*> m_pickups;
	std::vector<Enemy*> m_enemies;

	LTexture m_background;
public:
	Level();

	void Initialize(b2World*, SDL_Renderer*, Player*);
	void Update();
	void Draw(SDL_Renderer*, b2Vec2);
};

#endif