#include "Human.h"
#include "Game.h"
#include "ChessFigure.h"

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

std::vector<sf::Vector2i> Human::GetCanMovePos() const
{
	return std::vector<sf::Vector2i>();
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

bool Human::MoveMP()
{
	Game* game = Game::GetInstance();
	
	int nChecker = -1;

	for (int i = 0; i < m_figures.size(); i++)
	{
		if (*m_figures[i] == game->m_dataPacket.m_starterPos)
		{
			/*m_NbeatChecker = i;
			return m_checkers[i].Move(sf::Vector2f(game->m_dataPacket.m_finishPos.y * 56 + 29, game->m_dataPacket.m_finishPos.x * 56 +29), true, m_queened).second;*/
		}
	}
	return false;
}
