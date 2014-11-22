#include "Level.h"

Level::Level(){
}

void Level::Initialize(b2World* w,SDL_Renderer* r, Player* p)
{

	m_background.loadFromFile("background.png", r);
	m_player = p;
	m_enemies.push_back(new Enemy(w, r, b2Vec2(600, 300), 50));
}

void Level::Update(){
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Update(m_player->GetPosition());
	}
}

void Level::Draw(SDL_Renderer* r, b2Vec2 offset)
{
	m_background.render(-offset.x, offset.y, NULL, 0, 0, SDL_FLIP_NONE, r);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Draw(r, offset);
	}
}

