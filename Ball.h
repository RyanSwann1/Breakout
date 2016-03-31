#ifndef BALL_H
#define BALL_H

#include "MoveDirection.h"
#include "Entity.h"
#include <SDL.h>
#include <vector>
#include <list>
struct Entity;
struct MoveDirection;
class Game;
class Player;
class Ball
{
public:
	Ball(const Player& player);
	~Ball();

	SDL_Rect getPos() const { return m_pos; }
	bool collision(const SDL_Rect& ballPos, const SDL_Rect& entityPos) const;

	void movement(Game& game, const Player& player, std::vector<Entity>& balls);
	void releaseBall(std::vector<Entity>& balls);
	void changeDir(const MoveDirection& dir) { m_dir = dir; }
	void manageBounds(Game& game, std::vector<Entity>& balls);
	
	//Getters
	MoveDirection getReflection(const SDL_Rect& pos, int hitPos, const MoveDirection& dir) const;
	MoveDirection getBlockReflection(const SDL_Rect& pos, int hitPos, const MoveDirection& dir) const;

private:
	SDL_Rect m_pos; //Position of ball;
	MoveDirection m_dir;

	int m_movementSpeed;
	int m_spawnXPos;
	int m_spawnYPos;
	int m_sizeWidth;
	int m_sizeHeight;

};

#endif // !BALL_H