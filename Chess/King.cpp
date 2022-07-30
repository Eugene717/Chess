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

	if (!m_firstTurn)  //castling
	{
		for (size_t i = m_pos.x + 1; i < 8; i++)  //right
		{
			if (game->m_board[i][m_pos.y] != nullptr)
				if (game->m_board[i][m_pos.y]->GetStatus() == 'r')  //rock
				{
					if (!game->m_board[i][m_pos.y]->FirstTurn())
					{
						pos.push_back(sf::Vector2i(i - 1, m_pos.y));  //castling
						//pos.push_back(sf::Vector2i(i, m_pos.y));
					}
				}
				else
					break;
		}
		for (size_t i = m_pos.x - 1; i >= 0; i--)  //left
		{
			if (game->m_board[i][m_pos.y] != nullptr)
				if (game->m_board[i][m_pos.y]->GetStatus() == 'r')  //rock
				{
					if (!game->m_board[i][m_pos.y]->FirstTurn())
					{
						pos.push_back(sf::Vector2i(i + 2, m_pos.y));  //castling
						//pos.push_back(sf::Vector2i(i, m_pos.y));
					}
				}
				else
					break;
		}
	}

	return pos;
}

bool King::Move()
{
	Game* game = Game::GetInstance();
	std::vector<sf::Vector2i> canMove = CanMove();

	for (auto& i : canMove)
	{
		if (i.x * 100 < m_sprite.getPosition().x && i.x * 100 + 100 > m_sprite.getPosition().x)
		{
			if (i.y * 100 < m_sprite.getPosition().y && i.y * 100 + 100 > m_sprite.getPosition().y)
			{

				m_sprite.setPosition(i.x * 100 + 50, i.y * 100 + 50);

				bool beated = false;

				if (abs(m_pos.x - i.x) > 1)
				{
					if (m_pos.x < i.x)
					{
						game->m_board[7][i.y]->setPosition(5 * 100 + 50, m_sprite.getPosition().y);
						game->m_board[7][i.y]->Move();

						game->m_board[i.x][i.y] = game->m_board[m_pos.x][m_pos.y];
						game->m_board[m_pos.x][m_pos.y] = nullptr;
					}
					else
					{
						game->m_board[0][i.y]->setPosition(3 * 100 + 50, m_sprite.getPosition().y);
						game->m_board[0][i.y]->Move();

						game->m_board[i.x][i.y] = game->m_board[m_pos.x][m_pos.y];
						game->m_board[m_pos.x][m_pos.y] = nullptr;
					}
				}
				else if (game->m_board[i.x][i.y] != nullptr)
				{
					game->m_board[i.x][i.y]->Kill();
					game->m_board[i.x][i.y] = game->m_board[m_pos.x][m_pos.y];
					game->m_board[m_pos.x][m_pos.y] = nullptr;
					beated = true;
				}
				else
				{
					game->m_board[i.x][i.y] = game->m_board[m_pos.x][m_pos.y];
					game->m_board[m_pos.x][m_pos.y] = nullptr;
				}

				m_pos = i;
				m_firstTurn = true;

				if (beated)
					m_beat.play();
				else
					m_move.play();

				return true;
			}
		}
	}

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
	return false;
}
