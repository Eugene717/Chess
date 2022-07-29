#include "King.h"
#include "Game.h"

King::King(sf::Vector2i&& pos, char&& color) noexcept : ChessFigure(std::move(pos), std::move(color))
{
	if (m_color == 'w')
		m_texture.loadFromFile("resourses/images/wk.png");
	else if (m_color == 'b')
		m_texture.loadFromFile("resourses/images/bk.png");

	m_alived = 'k';

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
}

std::vector<sf::Vector2i> King::CanMove() const
{
	Game* game = Game::GetInstance();

	std::vector<sf::Vector2i> pos;

	if (m_pos.y > 0)
	{
		if (game->m_board[m_pos.x][m_pos.y - 1] == nullptr)  // just move
			pos.push_back(sf::Vector2i(m_pos.x, m_pos.y - 1));
		else if (game->m_board[m_pos.x][m_pos.y - 1]->GetColor() != m_color)
			pos.push_back(sf::Vector2i(m_pos.x, m_pos.y - 1));  // beat

		if (m_pos.x > 0)
		{
			if (game->m_board[m_pos.x - 1][m_pos.y - 1] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y - 1));
			else if(game->m_board[m_pos.x - 1][m_pos.y - 1]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y - 1));  // beat
		}
		if (m_pos.x < 7)
		{
			if (game->m_board[m_pos.x + 1][m_pos.y - 1] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y - 1));
			else if (game->m_board[m_pos.x + 1][m_pos.y - 1]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y - 1));  // beat
		}
	}
	if (m_pos.y < 7)
	{
		if (game->m_board[m_pos.x][m_pos.y + 1] == nullptr)  // just move
			pos.push_back(sf::Vector2i(m_pos.x, m_pos.y + 1));
		else if (game->m_board[m_pos.x][m_pos.y + 1]->GetColor() != m_color)
			pos.push_back(sf::Vector2i(m_pos.x, m_pos.y + 1));  // beat

		if (m_pos.x > 0)
		{
			if (game->m_board[m_pos.x - 1][m_pos.y + 1] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y + 1));
			else if (game->m_board[m_pos.x - 1][m_pos.y + 1]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y + 1));  // beat
		}
		if (m_pos.x < 7)
		{
			if (game->m_board[m_pos.x + 1][m_pos.y + 1] == nullptr)  // just move
				pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y + 1));
			else if (game->m_board[m_pos.x + 1][m_pos.y + 1]->GetColor() != m_color)
				pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y + 1));  // beat
		}
	}
	if (m_pos.x > 0)
		if (game->m_board[m_pos.x - 1][m_pos.y] == nullptr)  // just move
			pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y));
		else if (game->m_board[m_pos.x - 1][m_pos.y]->GetColor() != m_color)
			pos.push_back(sf::Vector2i(m_pos.x - 1, m_pos.y));  // beat
	if (m_pos.x < 7)
		if (game->m_board[m_pos.x + 1][m_pos.y] == nullptr)  // just move
			pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y));
		else if (game->m_board[m_pos.x + 1][m_pos.y]->GetColor() != m_color)
			pos.push_back(sf::Vector2i(m_pos.x + 1, m_pos.y));  // beat

	if (m_firstTurn)
	{
		for (size_t i = m_pos.x + 1; i < 8; i++)  //right
		{
			//if (game->m_board[i][m_pos.y]->GetStatus() == 'r')  //rock
			//	if (game->m_board[i][m_pos.y])
			//		nullptr;
		}
	}

	return pos;
}
