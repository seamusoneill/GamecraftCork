#include "include/Level.h"


Level::Level(){
}

void Level::Initialize(b2World* w, SDL_Renderer* r, Player* p)
{

	m_background.loadFromFile("background.png", r);
	m_player = p;
	m_island = new Island(900, 300, 0, 1, r, w);
	m_enemies.push_back(new Enemy(w, r, b2Vec2(600, 300), 50));
	m_enemies.push_back(new Enemy(w, r, b2Vec2(0, 300), 50));
	m_enemies.push_back(new Enemy(w, r, b2Vec2(600, 0), 50));
	m_enemies.push_back(new Enemy(w, r, b2Vec2(0, 0), 50));


	m_pickups.push_back(new PickUp(w, r, b2Vec2(100, 100), true));
}

void Level::Update(b2Vec2 offset){
	m_offset = offset;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if(m_enemies[i]->GetAlive())
			m_enemies[i]->Update(m_player->GetPosition(), m_player->GetVelocity());
	}
	for (int i = 0; i < m_pickups.size(); i++)
	{
		m_pickups[i]->Update();
	}
}

void Level::Draw(SDL_Renderer* r)
{
	m_background.render(-CONSTANTS::LEVEL_WIDTH / 2 - m_offset.x, -CONSTANTS::LEVEL_HEIGHT / 2 + m_offset.y, NULL, 0, 0, SDL_FLIP_NONE, r);
	m_island->Draw(r, m_offset);
	
}

int Level::DrawEnemies(void* rendererData)
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Draw(static_cast<SDL_Renderer*>(rendererData), m_offset);

		for (int j = 0; j < m_enemies[i]->cannonBalls.size(); j++)
		{
			m_enemies[i]->cannonBalls[j]->Draw(static_cast<SDL_Renderer*>(rendererData),m_offset);
		}
	}
	return 0;
}

int Level::DrawPickups(void* rendererData)
{
	for (int i = 0; i < m_pickups.size(); i++)
	{
		m_pickups[i]->Draw(static_cast<SDL_Renderer*>(rendererData), m_offset);
	}
	return 0;
}