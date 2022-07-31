#include "Human.h"
#include "Game.h"
#include "ChessFigure.h"
#include "Queen.h"
#include "Bishop.h"
#include "Horse.h"
#include "Rock.h"

Human::Human(char&& color) :Player(std::move(color))
{ }

void Human::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Game* game = Game::GetInstance();

	for (auto i : m_figures)
	{
		if (m_p_moved_figure != i)
			game->m_window.draw(*i);
	}
	if (m_p_moved_figure != nullptr)
		game->m_window.draw(*m_p_moved_figure);
}

void Human::PawnChange(const char& figure)
{
	if (figure == 'q')
	{
		ChessFigure* temp = new Queen(m_p_moved_figure->GetPosition(), GetColor());
		delete m_p_moved_figure;
		(*std::find(m_figures.begin(), m_figures.end(), m_p_moved_figure)) = temp;
	}
	else if (figure == 'b')
	{
		ChessFigure* temp = new Bishop(m_p_moved_figure->GetPosition(), GetColor());
		delete m_p_moved_figure;
		(*std::find(m_figures.begin(), m_figures.end(), m_p_moved_figure)) = temp;
	}
	else if (figure == 'h')
	{
		ChessFigure* temp = new Horse(m_p_moved_figure->GetPosition(), GetColor());
		delete m_p_moved_figure;
		(*std::find(m_figures.begin(), m_figures.end(), m_p_moved_figure)) = temp;
	}
	else if (figure == 'r')
	{
		ChessFigure* temp = new Rock(m_p_moved_figure->GetPosition(), GetColor());
		delete m_p_moved_figure;
		(*std::find(m_figures.begin(), m_figures.end(), m_p_moved_figure)) = temp;
	}
}

bool Human::Move()
{
	Game* game = Game::GetInstance();
	bool isMove = false;
	sf::Vector2f pos;
	std::vector<sf::Vector2i>* possiblePos = nullptr;

	while (game->m_window.isOpen())
	{
		pos = game->m_window.mapPixelToCoords(sf::Mouse::getPosition(game->m_window));

		if (game->m_window.pollEvent(game->m_event))
		{
			if (game->m_event.type == sf::Event::Closed)
			{
				game->m_dataPacket.m_finishGame = true;
				game->m_window.close();
				return false;
			}
			if (game->m_event.type == sf::Event::MouseButtonPressed)
			{
				if (game->m_event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < m_figures.size(); i++)
					{
						if (sf::IntRect(m_figures[i]->getGlobalBounds()).contains(sf::Mouse::getPosition(game->m_window)))
						{
							isMove = true;
							m_p_moved_figure = m_figures[i];
							break;
						}
					}
				}
			}
			if (game->m_event.type == sf::Event::MouseButtonReleased)
			{
				if (game->m_event.key.code == sf::Mouse::Left)
				{
					if (isMove)
					{
						delete possiblePos;
						possiblePos = nullptr;

						game->DrawGame();

						game->m_dataPacket.m_starterPos.x = m_p_moved_figure->GetPosition().x;
						game->m_dataPacket.m_starterPos.y = m_p_moved_figure->GetPosition().y;

						if (!m_p_moved_figure->Move())
						{
							m_p_moved_figure = nullptr;
							isMove = false;
							continue;
						}

						game->m_dataPacket.m_finishPos.x = m_p_moved_figure->GetPosition().x;
						game->m_dataPacket.m_finishPos.y = m_p_moved_figure->GetPosition().y;

						game->DrawGame();

						if (m_p_moved_figure->GetStatus() == 'p')
						{
							if (GetColor() == 'w')
							{
								if (m_p_moved_figure->GetPosition().y == 0)
									PawnChange(PawnUp());
							}
							else
							{
								if (m_p_moved_figure->GetPosition().y == 7)
									PawnChange(PawnUp());
							}
						}

						m_p_moved_figure = nullptr;

						return true;
					}
				}
			}
		}
		if (isMove)
		{
			m_p_moved_figure->setPosition(pos.x, pos.y);

			if (possiblePos == nullptr)
			{
				possiblePos = new std::vector<sf::Vector2i>(m_p_moved_figure->CanMove());
			}

			game->DrawPossibleMoves(*possiblePos, GetColor());
		}
		else
			game->DrawGame();
	}
}

bool Human::MoveMP(sf::TcpSocket& socket)
{
	Game* game = Game::GetInstance();

	GameDataPacket* dataPacket = &game->m_dataPacket;
	sf::Packet packet;

	while (game->m_window.isOpen())
	{
		while (game->m_window.pollEvent(game->m_event))
		{
			if (game->m_event.type == sf::Event::Closed)
				game->m_window.close();
		}

		game->m_window.clear(sf::Color::White);
		game->DrawGame();

		sf::Socket::Status status = socket.receive(packet);
		if (status == sf::Socket::Disconnected)
			return false;
		if (status == sf::Socket::Done)
		{
			packet >> *dataPacket;
			packet.clear();

			for (int i = 0; i < m_figures.size(); i++)
			{
				if (*m_figures[i] == game->m_dataPacket.m_starterPos)
				{
					m_figures[i]->setPosition(game->m_dataPacket.m_finishPos.x * 100 + 50, game->m_dataPacket.m_finishPos.y * 100 + 50);
					return m_figures[i]->Move();
				}
			}
		}
	}
	return false;
}
