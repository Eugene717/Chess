#include "ChessFigure.h"
#include "Game.h"

int ChessFigure::ChessNum = 0;
sf::SoundBuffer ChessFigure::m_moveBuf;
sf::Sound ChessFigure::m_move;
sf::SoundBuffer ChessFigure::m_beatBuf;
sf::Sound ChessFigure::m_beat;

void ChessFigure::LoadFiles()
{
	if (ChessNum == 0)
	{
		m_moveBuf.loadFromFile("resourses/sounds/move.wav");
		m_move.setBuffer(m_moveBuf);
		m_beatBuf.loadFromFile("resourses/sounds/beat.wav");
		m_beat.setBuffer(m_beatBuf);
	}
	++ChessNum;
}

ChessFigure::ChessFigure(sf::Vector2i&& pos,const char& color) noexcept : m_pos(std::move(pos)), m_color(color)
{
	LoadFiles();

	m_sprite.setOrigin(50, 50);
	m_firstTurn = false;
}

ChessFigure::~ChessFigure()
{
	--ChessNum;
}

char ChessFigure::GetColor() const
{
	return m_color;
}

void ChessFigure::Kill()
{
	m_alived = 'X';
}

bool ChessFigure::CheckAlived() const
{
	if (m_alived == 'X')
		return false;
	else
		return true;
}

char ChessFigure::GetStatus() const
{
	return m_alived;
}

bool ChessFigure::FirstTurn() const
{
	return m_firstTurn;
}

bool ChessFigure::operator==(const sf::Vector2i& other)
{
	return m_pos.x == other.x && m_pos.y == other.y;
}

void ChessFigure::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

sf::FloatRect ChessFigure::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

void ChessFigure::setPosition(const float& x, const float& y)
{
	m_sprite.setPosition(x, y);
}

sf::Vector2i ChessFigure::GetPosition() const
{
	return m_pos;
}	

bool ChessFigure::Move()
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

				if (game->m_board[i.x][i.y] != nullptr)
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
