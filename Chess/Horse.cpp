#include "Horse.h"
#include "Game.h"

Horse::Horse(sf::Vector2i&& pos, char&& color) noexcept : ChessFigure(std::move(pos), std::move(color))
{
	if (m_color == 'w')
		m_texture.loadFromFile("resourses/images/wh.png");
	else if (m_color == 'b')
		m_texture.loadFromFile("resourses/images/bh.png");

	m_alived = 'h';

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
}

std::vector<sf::Vector2i> Horse::CanMove() const
{
	Game* game = Game::GetInstance();

	std::vector<sf::Vector2i> pos;

	if (m_pos.y > 1)  //up
	{
		if (m_pos.x > 0)
		{
			if (game->m_board[m_pos.x - 1][m_pos.y - 2] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y - 2));
			else if (game->m_board[m_pos.x - 1][m_pos.y - 2]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y - 2));  // beat
		}
		if (m_pos.x < 7)
		{
			if (game->m_board[m_pos.x + 1][m_pos.y - 2] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y - 2));
			else if (game->m_board[m_pos.x + 1][m_pos.y - 2]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y - 2));  // beat
		}
	}
	if (m_pos.y < 6)  //donw
	{
		if (m_pos.x > 0)
		{
			if (game->m_board[m_pos.x - 1][m_pos.y + 2] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y + 2));
			else if (game->m_board[m_pos.x - 1][m_pos.y + 2]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y + 2));  // beat
		}
		if (m_pos.x < 7)
		{
			if (game->m_board[m_pos.x + 1][m_pos.y + 2] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y + 2));
			else if (game->m_board[m_pos.x + 1][m_pos.y + 2]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y + 2));  // beat
		}
	}
	if (m_pos.x > 1)  // left
	{
		if (m_pos.y > 0)
		{
			if (game->m_board[m_pos.x - 2][m_pos.y - 1] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x - 2, m_pos.y - 1));
			else if (game->m_board[m_pos.x - 2][m_pos.y - 1]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x - 2, m_pos.y - 1));  // beat
		}
		if (m_pos.y < 7)
		{
			if (game->m_board[m_pos.x - 2][m_pos.y + 1] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x - 2, m_pos.y + 1));
			else if (game->m_board[m_pos.x - 2][m_pos.y + 1]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x - 2, m_pos.y + 1));  // beat
		}
	}
	if (m_pos.x < 6)  //right
	{
		if (m_pos.y > 0)
		{
			if (game->m_board[m_pos.x + 2][m_pos.y - 1] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x + 2, m_pos.y - 1));
			else if (game->m_board[m_pos.x + 2][m_pos.y - 1]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x + 2, m_pos.y - 1));  // beat
		}
		if (m_pos.y < 7)
		{
			if (game->m_board[m_pos.x + 2][m_pos.y + 1] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x + 2, m_pos.y + 1));
			else if (game->m_board[m_pos.x + 2][m_pos.y + 1]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x + 2, m_pos.y + 1));  // beat
		}
	}

	return pos;
}
