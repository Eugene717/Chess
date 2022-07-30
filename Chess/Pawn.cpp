#include "Pawn.h"
#include "Game.h"
#include "Queen.h"
#include "Bishop.h"
#include "Horse.h"
#include "Rock.h"

Pawn::Pawn(sf::Vector2i&& pos, char&& color) noexcept : ChessFigure(std::move(pos), std::move(color))
{
	if (m_color == 'w')
		m_texture.loadFromFile("resourses/images/wp.png");
	else if (m_color == 'b')
		m_texture.loadFromFile("resourses/images/bp.png");

	m_alived = 'p';

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
}

std::vector<sf::Vector2i> Pawn::CanMove() const
{
	Game* game = Game::GetInstance();

	std::vector<sf::Vector2i> pos;

	if (m_color == 'w')
	{
		if (game->m_board[m_pos.x][m_pos.y - 1] == nullptr)  // just move
		{
			pos.push_back(sf::Vector2i(m_pos.x, m_pos.y - 1));
		}		
		if (!m_firstTurn)
			if (!pos.empty())
				if (game->m_board[m_pos.x][m_pos.y - 2] == nullptr)
					pos.push_back(sf::Vector2i(m_pos.x, m_pos.y - 2));

		if (m_pos.x > 0 && m_pos.y > 0)
			if (game->m_board[m_pos.x - 1][m_pos.y - 1] != nullptr)  //beat
			{
				if (game->m_board[m_pos.x - 1][m_pos.y - 1]->GetColor() != m_color)
					pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y - 1));
			}
		if (m_pos.x < 7 && m_pos.y > 0)
			if (game->m_board[m_pos.x + 1][m_pos.y - 1] != nullptr)  //beat
			{
				if (game->m_board[m_pos.x + 1][m_pos.y - 1]->GetColor() != m_color)
					pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y - 1));
			}
	}
	else
	{
		if (game->m_board[m_pos.x][m_pos.y + 1] == nullptr)
		{
			pos.push_back(sf::Vector2i(m_pos.x, m_pos.y + 1));
		}
		if (!m_firstTurn)
			if (!pos.empty())
				if (game->m_board[m_pos.x][m_pos.y + 2] == nullptr)
					pos.push_back(sf::Vector2i(m_pos.x, m_pos.y + 2));

		if (m_pos.x > 0 && m_pos.y < 7)
			if (game->m_board[m_pos.x - 1][m_pos.y + 1] != nullptr)  //beat
			{
				if (game->m_board[m_pos.x - 1][m_pos.y + 1]->GetColor() != m_color)
					pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y + 1));
			}
		if (m_pos.x < 7 && m_pos.y < 7)
			if (game->m_board[m_pos.x + 1][m_pos.y + 1] != nullptr)  //beat
			{
				if (game->m_board[m_pos.x + 1][m_pos.y + 1]->GetColor() != m_color)
					pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y + 1));
			}
	}

	return pos;
}

