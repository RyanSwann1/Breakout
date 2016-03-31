#ifndef ENTITY_H
#define ENTITY_H

#include "MoveDirection.h"
#include <SDL.h>

struct Entity
{
	Entity(SDL_Rect pos)
	{
		m_pos.x = pos.x;
		m_pos.y = pos.y;
		m_pos.h = pos.h;
		m_pos.w = pos.w;
	}
	Entity(SDL_Rect pos, const int movementSpeed)
	{
		m_pos.x = pos.x;
		m_pos.y = pos.y;
		m_pos.h = pos.h;
		m_pos.w = pos.w;
		m_movementSpeed = movementSpeed;
	}

	Entity(SDL_Rect pos, const int movementSpeed, MoveDirection& dir) 
	{
		m_pos.x = pos.x;
		m_pos.y = pos.y;
		m_pos.h = pos.h;
		m_pos.w = pos.w;
		m_movementSpeed = movementSpeed;
		m_dir = dir;
	}

	SDL_Rect m_pos; //Position of entity
	MoveDirection m_dir; //Move Direction of entity;
	int m_movementSpeed; //Movement speed of entity
};
#endif // !ENTITY_H
