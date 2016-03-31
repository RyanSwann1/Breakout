#include "Game.h"
#include "Window.h"
#include "Player.h"
#include "Ball.h"
#include "MoveDirection.h"


#include <random>
#include <iostream>

Game::Game(const Window& window)
{
	m_gameOver = false;
	m_holdBall = true;
	m_playingFieldWidth = window.getScreenWidth();
	m_playingFieldHeight = window.getScreenHeight();
	spawnBlocks();
}


Game::~Game()
{
}

void Game::inputManager(Player & player, const Game& game, Ball& ball)
{
	MoveDirection dir;
	const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

	//Move player to the right
	if (keyState[SDL_SCANCODE_D]) 
	{
		dir.dirX = 1;
		dir.dirY = 0;
		player.movement(dir, game);
	}

	//Move player left
	else if (keyState[SDL_SCANCODE_A]) 
	{
		dir.dirX = -1;
		dir.dirY = 0;
		player.movement(dir, game);
	}

	//Release ball
	else if (keyState[SDL_SCANCODE_SPACE]) 
	{
		if (m_holdBall) 
		{
			m_holdBall = false;
			ball.releaseBall(m_balls);
		}
	}

	if (!m_holdBall)
	{
		if (keyState[SDL_SCANCODE_P])
		{
			SDL_Rect pos;
			pos.x = 300;
			pos.y = 300;
			pos.h = 10;
			pos.w = 10;
			int movementSpeed = 6;
			spawnBall(pos, movementSpeed);
		}
	}

}

void Game::render(const Player & player, const Ball & ball, const Window& window)
{
	SDL_RenderClear(window.getRenderer());

	//Render player
	SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(window.getRenderer(), &player.getPos());
	SDL_RenderFillRect(window.getRenderer(), &ball.getPos());
	//Render balls
	for (auto ballInstance : m_balls)
	{
		SDL_RenderFillRect(window.getRenderer(), &ballInstance.m_pos);
	}

	for (auto block : m_blocks) {
		SDL_RenderFillRect(window.getRenderer(), &block.m_pos);
	}
	
	//Render background
	SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 0);

	//Apply render
	SDL_RenderPresent(window.getRenderer());
}

void Game::update(Game& game, Player& player, Ball& ball)
{

	ball.movement(game, player, m_balls);
	ball.manageBounds(game, m_balls);

	
	//Handle collisions
	collisionManagement(player, ball);
}

void Game::spawnBall(SDL_Rect pos, const int movementSpeed)
{
	if (m_balls.empty()) {
		m_balls.push_back(Entity(pos, movementSpeed));
	}
	else
	{
		bool validPos = false;
		MoveDirection dir;
		while (!validPos) 
		{
			dir.dirX = getRandNumb(-1, 1);
			dir.dirY = getRandNumb(-1, 1);

			if (dir.dirX != 0 && dir.dirY != 0) {
				validPos = true;
			}
		}

		m_balls.push_back(Entity(pos, movementSpeed, dir));
	}
	
}


int Game::getRandNumb(const int min, const int max) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	return dis(gen);
}

void Game::collisionManagement(Player & player, Ball & ball)
{
	//Ball to player collision
	for (auto &ballsInstance : m_balls)
	{
		if (ball.collision(ballsInstance.m_pos, player.getPos())) 
		{
			std::cout << "Collision";
			//Send in center of ball

			ballsInstance.m_dir = ball.getReflection(player.getPos(), ballsInstance.m_pos.x + (ballsInstance.m_pos.w / 2), ballsInstance.m_dir);
			//ball.changeDir(ball.getReflection(player.getPos(), ball.getPos().x + (ball.getPos().w / 2)));
		}
	}

	//Ball to block collision
	for (auto &ballInstance : m_balls)
	{
		for (auto blockInstance : m_blocks)
		{
			if (ball.collision(ballInstance.m_pos, blockInstance.m_pos)) 
			{
				ballInstance.m_dir = ball.getBlockReflection(blockInstance.m_pos, ballInstance.m_pos.x + (ballInstance.m_pos.w / 2), ballInstance.m_dir);

			}
		}
	}



	////if Ball and Block collision
	//for (auto cIter = m_blocks.cbegin(); cIter != m_blocks.cend(); cIter++)
	//{
	//	if (ball.collision(cIter->m_pos)) 
	//	{
	//		ball.changeDir(ball.getBlockReflection(cIter->m_pos, ball.getPos().x + (ball.getPos().w / 2)));
	//		m_blocks.erase(cIter);
	//		break;
	//	}
	//}

	//If Ball and block collision
}

void Game::spawnBlocks()
{
	static constexpr int SIZE_WIDTH = 50;
	static constexpr int SIZE_HEIGHT = 10;
	int spawnXPos = 100;
	int spawnYPos = 100;
	int newXPos = 60;
	int newYPos = 100;

	for (int i = 0; i != TOTAL_BLOCKS; i++)
	{
		m_blocks.push_back(Entity({ spawnXPos, spawnYPos, SIZE_WIDTH, SIZE_HEIGHT }));
		spawnXPos += newXPos;
	}
		//m_blocks.push_back(Entity(spawnXPos, spawnYPos, SIZE_WIDTH, SIZE_HEIGHT)); 
	
	
}
