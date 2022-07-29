#include "Bishop.h"
#include "Game.h"

Bishop::Bishop(sf::Vector2i&& pos, char&& color) noexcept : ChessFigure(std::move(pos), std::move(color))
{
	if (m_color == 'w')
		m_texture.loadFromFile("resourses/images/wb.png");
	else if (m_color == 'b')
		m_texture.loadFromFile("resourses/images/bb.png");

	m_alived = 'b';

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
}

std::vector<sf::Vector2i> Bishop::CanMove() const
{
	Game* game = Game::GetInstance();

	std::vector<sf::Vector2i> pos;

	for (int i = m_pos.x + 1, j = m_pos.y + 1; i < 8 && j < 8; i++, j++)   //donw-right
	{
		if (game->m_board[i][j] == nullptr)  // just move
			pos.push_back(sf::Vector2i(i, j));
		else if (game->m_board[i][j]->GetColor() == m_color)
			break;
		else
		{
			pos.push_back(sf::Vector2i(i, j));  // beat
			break;
		}
	}
	for (int i = m_pos.x + 1, j = m_pos.y - 1; i < 8 && j >= 0; i++, j--)  //donw-left
	{
		if (game->m_board[i][j] == nullptr)  // just move
			pos.push_back(sf::Vector2i(i, j));
		else if (game->m_board[i][j]->GetColor() == m_color)
			break;
		else
		{
			pos.push_back(sf::Vector2i(i, j));  // beat
			break;
		}
	}
	for (int i = m_pos.x - 1, j = m_pos.y + 1; i >= 0 && j < 8; i--, j++)  //up-right
	{
		if (game->m_board[i][j] == nullptr)  // just move
			pos.push_back(sf::Vector2i(i, j));
		else if (game->m_board[i][j]->GetColor() == m_color)
			break;
		else
		{
			pos.push_back(sf::Vector2i(i, j));  // beat
			break;
		}
	}
	for (int i = m_pos.x - 1, j = m_pos.y - 1; i >= 0 && j >= 0; i--, j--)  //up-left
	{
		if (game->m_board[i][j] == nullptr)  // just move
			pos.push_back(sf::Vector2i(i, j));
		else if (game->m_board[i][j]->GetColor() == m_color)
			break;
		else
		{
			pos.push_back(sf::Vector2i(i, j));  // beat
			break;
		}
	}

	return pos;
}
