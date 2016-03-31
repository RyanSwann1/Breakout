#include "Ball.h"
#include "Player.h"
#include "Game.h"
#include "MoveDirection.h"


#include <iostream>
#include <algorithm>

Ball::Ball(const Player& player)
{
	m_sizeHeight = 10;
	m_sizeWidth = 10;

	//m_spawnXPos = player.getPos().x + (player.getPos().w / 2) - m_pos.w / 2;
	//m_spawnYPos = player.getPos().y - (player.getPos().h * 2);
	//Initialize pos and size of ball
	//m_pos.h = m_sizeHeight;
	//m_pos.w = m_sizeWidth;
	//m_pos.x = player.getPos().x + (player.getPos().w / 2) - m_pos.w / 2;
	//m_pos.y = player.getPos().y - (player.getPos().h * 2);
	//Initialize dir of ball
	m_dir.dirX = 0;
	m_dir.dirY = 0;
	m_movementSpeed = 6;
	
	
}

Ball::~Ball()
{
}

bool Ball::collision(const SDL_Rect & ballPos, const SDL_Rect& entityPos) const
{
	//if collision
	if (ballPos.x + ballPos.w > entityPos.x && ballPos.x < entityPos.x + entityPos.w &&
		ballPos.y + ballPos.h > entityPos.y && ballPos.y < entityPos.y + entityPos.h) {
		return true;
	}
	//if no collision
	else {
		return false;
	}


	//for (auto &ball : m_balls)
	//{
	//	//If collison
	//	if (ball.m_pos.x + ball.m_pos.w > pos.x && ball.m_pos.x < pos.x + pos.w &&
	//		ball.m_pos.y + ball.m_pos.h > pos.y && ball.m_pos.y < pos.y + pos.h) {
	//		std::cout << "Collsion";
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

}

MoveDirection Ball::getReflection(const SDL_Rect & pos, int hitPos, const MoveDirection& dir) const
{
	MoveDirection newDir; //New direction of movement


	hitPos -= pos.x; //Get hit position relative to player
	int offSet = pos.w / 3; //Split up into three parts for three different directional movements
	int playerCenterPos = pos.w / 2;

	//Keep within bounds of pos
	if (hitPos < 0) {
		hitPos = 0;
	}
	else if (hitPos > pos.w) {
		hitPos = pos.w;
	}

		//if ball is moving Down
		if (dir.dirY == 1)
		{
			newDir.dirY = -1; //Change y axis

			if (hitPos < playerCenterPos - offSet) {
				newDir.dirX = -1;
			}

			else if (hitPos > playerCenterPos + offSet) {
				newDir.dirX = 1;
			}
			else
			{
				newDir.dirX = 0;
			}
		}

		//If ball is moving Up
		else if(dir.dirY == -1)
		{
			newDir.dirY = 1; //Change y axis. 

			if (hitPos < playerCenterPos - offSet) {
				newDir.dirX = -1;
			}

			else if (hitPos > playerCenterPos + offSet) {
				newDir.dirX = 1;
			}
			else
			{
				newDir.dirX = 0;
			}
		}
		
	std::cout << hitPos << "\n";
	return newDir;
}

MoveDirection Ball::getBlockReflection(const SDL_Rect & pos, int hitPos, const MoveDirection& dir) const
{
	MoveDirection newDir; //New direction in which ball will move
	
	//If ball is moving up
	if (dir.dirY == -1)
	{
		newDir.dirY = 1;

		//If already moving left, keep same direction
		if (dir.dirX == -1) {
			newDir.dirX = -1;
		}
		//If already moving right, keep same direction
		else if (dir.dirX == 1) {
			newDir.dirX = 1;
		}

		else {
			newDir.dirX = 0;
		}
	}
	else if (dir.dirY == 1)
	{
		newDir.dirY = -1;

		//If already moving left, keep same direction
		if (dir.dirX == -1) {
			newDir.dirX = -1;
		}
		//If already moving right, keep same direction
		else if (dir.dirX == 1) {
			newDir.dirX = 1;
		}

		else {
			newDir.dirX = 0;
		}
	}
	return newDir;
}

void Ball::movement(Game & game, const Player & player, std::vector<Entity>& balls)
{
	if (balls.empty())
	{
		int spawnXPos = player.getPos().x + (player.getPos().w / 2) - m_sizeWidth / 2;
		int spawnYPos = player.getPos().y - (player.getPos().h * 2);
		game.spawnBall({ spawnXPos, spawnYPos, m_sizeWidth, m_sizeHeight }, m_movementSpeed);
		game.holdBall();
	}

	if (game.isBallHold())
	{
		for (auto &ballInstance : balls)
		{
			//std::cout << "Hi";
			ballInstance.m_pos.x = player.getPos().x + (player.getPos().w / 2) - m_sizeWidth / 2;
			ballInstance.m_pos.y = player.getPos().y - (player.getPos().h * 2);
		}
		//game.getBalls().front().m_pos.x = 
		//game.getBalls().front().m_pos.y = 
		//m_balls.front().m_pos
	}

	else
	{
		//Move all balls
		for (auto &ballInstance : balls)
		{
			switch (ballInstance.m_dir.dirX)
			{
			case -1: ballInstance.m_pos.x -= m_movementSpeed; break;
			case 1: ballInstance.m_pos.x += m_movementSpeed; break;
			}

			switch (ballInstance.m_dir.dirY)
			{
			case -1: ballInstance.m_pos.y -= m_movementSpeed; break;
			case 1: ballInstance.m_pos.y += m_movementSpeed; break;
			}
		}
	}

	//Move all balls
	//else
	//{
	//	switch (m_dir.dirX)
	//	{
	//	case -1: m_balls.front().m_pos.x -= m_movementSpeed; break;
	//	case 1: m_balls.front().m_pos.x += m_movementSpeed; break;
	//	}
	//	
	//	switch (m_dir.dirY)
	//	{
	//	case -1: m_balls.front().m_pos.y -= m_movementSpeed; break;
	//	case 1: m_balls.front().m_pos.y += m_movementSpeed; break;
	//	}
	//}

	////Move all balls 
	//if (m_balls.size() > 0)
	//{
	//	int ballPos = 0;
	//	for (auto ball : m_balls)
	//	{
	//		ballPos++;
	//		if (ballPos > 0)
	//		{
	//		}
	//	}
	//}
	
}

void Ball::releaseBall(std::vector<Entity>& balls)
{
	balls.front().m_dir.dirY = -1;
}

void Ball::manageBounds(Game& game, std::vector<Entity>& balls)
{
	for (auto iter = balls.begin(); iter != balls.end(); iter++)
	{
		//If ball touches left wall
		if (iter->m_pos.x <= 0)
		{
			//Reverse diagonal movement
			if (iter->m_dir.dirX == -1)
			{
				iter->m_dir.dirX = 1;
			}
		}

		//if ball touches the right wall
		else if (iter->m_pos.x + iter->m_pos.w >= game.getPlayingFieldWidth())
		{
			//Reverse ball diagonal movement
			if (iter->m_dir.dirX == 1) {
				iter->m_dir.dirX = -1;
			}
		}

		//If ball touches the top wall
		else if (iter->m_pos.y <= 0)
		{
			if (iter->m_dir.dirX == -1 && iter->m_dir.dirY == 0)
			{
				iter->m_dir.dirY = 1;
				iter->m_dir.dirX = 1;
			}

			else if (iter->m_dir.dirY == -1) {
				iter->m_dir.dirY = 1;
			}
		}

		else if (iter->m_pos.y >= game.getPlayingFieldHeight())
		{
			balls.erase(iter);
			return;
		}

		//iter++;
	}
}
