#include "Level.h"

Level::Level(){
}

void Level::Initialize(b2World* w,SDL_Renderer* r, Player* p)
{

	m_background.loadFromFile("background.png", r);
	m_player = p;
	m_island = new Island(900, 300, 0, 1, r, w);
	m_enemies.push_back(new Enemy(w, r, b2Vec2(600, 300), 50));
	m_pickups.push_back(new PickUp(w, r, b2Vec2(100, 100), true));
}

void Level::Update(){

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if(m_enemies[i]->GetAlive() == true)
		{
			m_enemies[i]->Update(m_player->GetPosition(),m_player->GetVelocity());
		}
	}
	for (int i = 0; i < m_pickups.size(); i++)
	{
		m_pickups[i]->Update();
	}
}

void Level::Draw(SDL_Renderer* r, b2Vec2 offset)
{
	m_background.render(-CONSTANTS::LEVEL_WIDTH/2 - offset.x, -CONSTANTS::LEVEL_HEIGHT/2 + offset.y, NULL, 0, 0, SDL_FLIP_NONE, r);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if(m_enemies[i]->GetAlive() == true)
		{
			m_enemies[i]->Draw(r, offset);
		}

		for(int j = 0; j < m_enemies[i]->cannonBalls.size();j++)
		{
			m_enemies[i]->cannonBalls[j]->Draw(r, offset);
		}
	}


	for (int i = 0; i < m_pickups.size(); i++)
	{
		m_pickups[i]->Draw(r, offset);
	}

	m_island->Draw(r,offset);
}

