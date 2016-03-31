#include "Player.h"
#include "MoveDirection.h"
#include "Game.h"

Player::Player(const Game& game)
{
	m_sizeHeight = 10;
	m_sizeWidth = 50;

	m_pos.x = (game.getPlayingFieldWidth() / 2) - m_sizeWidth / 2;
	m_pos.y = 650;
	m_pos.w = m_sizeWidth;
	m_pos.h = m_sizeHeight;

	m_movementSpeed = 6;
}

Player::~Player()
{
}

void Player::movement(const MoveDirection & dir, const Game& game)
{

	switch (dir.dirX)
	{
	case -1:
	{
		if (m_pos.x >= 0) {
			m_pos.x -= m_movementSpeed; 
		}
		break;
	}
	case 1: 
	{
		if (m_pos.x <= game.getPlayingFieldWidth() - m_pos.w) {
			m_pos.x += m_movementSpeed;
		}
		break;
	}
	}

}
