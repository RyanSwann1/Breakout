#ifndef GAME_H
#define GAME_H

#include "Entity.h"
#include <SDL.h>
#include <list>
#include <vector>

struct Entity;
struct MoveDirection;
class Ball;
class Player;
class Window;
class Game
{
public:
	Game(const Window& window);
	~Game();

	void endGame() { m_gameOver = true; }
	void inputManager(Player& player, const Game& game, Ball& ball);
	void render(const Player& player, const Ball& ball, const Window& window);
	void update(Game& game, Player& player, Ball& ball);
	void holdBall() { m_holdBall = true; }
	void spawnBall(SDL_Rect pos, const int movementSpeed);
	

	bool isGameOver() const { return m_gameOver; }
	bool isBallHold() const { return m_holdBall; }

	//Setters


	//Getters
	int getPlayingFieldHeight() const { return m_playingFieldHeight; }
	int getPlayingFieldWidth() const { return m_playingFieldWidth; }
	int getRandNumb(const int min, const int max) const;
	std::vector<Entity> getBalls() const { return m_balls; }



private:
	bool m_gameOver;
	bool m_holdBall;
	int m_playingFieldHeight;
	int m_playingFieldWidth;
	std::list<Entity> m_blocks;
	std::vector<Entity> m_balls;
	void collisionManagement(Player& player, Ball& ball);
	void spawnBlocks();

	static constexpr int TOTAL_BLOCKS = 9;
	
	//std::list<Ball> m_extraBalls;
};
#endif // !GAME_H

