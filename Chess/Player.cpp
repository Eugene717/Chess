#include "Player.h"
#include "Game.h"
#include "ChessFigure.h"
#include "Pawn.h"
#include "Rock.h"
#include "Horse.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

Player::Player(char&& color) :m_color(std::move(color))
{
	Game* game = Game::GetInstance();
	
	if (m_color == 'w')
	{
		for (size_t i = 0; i < 8; i++)
			m_figures.push_back(new Pawn(sf::Vector2i(i, 6), 'w'));

		m_figures.push_back(new Rock(sf::Vector2i(0, 7), 'w'));
		m_figures.push_back(new Rock(sf::Vector2i(7, 7), 'w'));

		m_figures.push_back(new Horse(sf::Vector2i(1, 7), 'w'));
		m_figures.push_back(new Horse(sf::Vector2i(6, 7), 'w'));

		m_figures.push_back(new Bishop(sf::Vector2i(2, 7), 'w'));
		m_figures.push_back(new Bishop(sf::Vector2i(5, 7), 'w'));

		m_figures.push_back(new Queen(sf::Vector2i(3, 7), 'w'));
		m_figures.push_back(new King(sf::Vector2i(4, 7), 'w'));
	}
	else
	{
		for (size_t i = 0; i < 8; i++)
			m_figures.push_back(new Pawn(sf::Vector2i(i, 1), 'b'));

		m_figures.push_back(new Rock(sf::Vector2i(0, 0), 'b'));
		m_figures.push_back(new Rock(sf::Vector2i(7, 0), 'b'));

		m_figures.push_back(new Horse(sf::Vector2i(1, 0), 'b'));
		m_figures.push_back(new Horse(sf::Vector2i(6, 0), 'b'));

		m_figures.push_back(new Bishop(sf::Vector2i(2, 0), 'b'));
		m_figures.push_back(new Bishop(sf::Vector2i(5, 0), 'b'));

		m_figures.push_back(new Queen(sf::Vector2i(3, 0), 'b'));
		m_figures.push_back(new King(sf::Vector2i(4, 0), 'b'));
	}

	for (auto i : m_figures)
	{
		game->m_board[i->GetPosition().x][i->GetPosition().y] = i;
	}

	return;
}

Player::~Player()
{
	m_figures.clear();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Game* game = Game::GetInstance();

	for (auto i : m_figures)
	{
		game->m_window.draw(*i);
	}
}

bool Player::DeleteKilled()
{
	m_figures.erase(std::remove_if(m_figures.begin(), m_figures.end(), [&](ChessFigure* i) { if (i->CheckAlived()) return false; else return true; }), m_figures.end());

	if (m_figures.empty())
	{
		Game* game = Game::GetInstance();
		game->m_dataPacket.m_finishGame = true;
		return true;
	}
	else
		return false;
}

bool Player::KingKilled()
{
	return !m_figures[m_figures.size() - 1]->CheckAlived();
}

sf::Vector2i Player::GetKingPos() const
{
	return m_figures[m_figures.size() - 1]->GetPosition();
}

bool Player::CheckCheck(const sf::Vector2i& kingPos) const
{
	Game* game = Game::GetInstance();

	std::vector<sf::Vector2i> pos;

	for (int i = 0; i < m_figures.size() - 1; i++)
	{
		pos = m_figures[i]->CanMove();

		for (int j = 0; j < pos.size(); j++)
		{
			if (pos[j].x == kingPos.x && pos[j].y == kingPos.y)
				return true;
		}
	}

	return false;
}

char Player::GetColor() const
{
	return m_color;
}

char Player::PawnUp()
{
	Game* game = Game::GetInstance();

	sf::Texture t_queen;  sf::Sprite s_queen;
	sf::Texture t_bishop; sf::Sprite s_bishop;
	sf::Texture t_horse;  sf::Sprite s_horse;
	sf::Texture t_rock;   sf::Sprite s_rock;

	if (m_color == 'w')
	{
		t_queen.loadFromFile("resourses/images/wq.png");
		t_bishop.loadFromFile("resourses/images/wb.png");
		t_horse.loadFromFile("resourses/images/wh.png");
		t_rock.loadFromFile("resourses/images/wr.png");
	}
	else
	{
		t_queen.loadFromFile("resourses/images/bq.png");
		t_bishop.loadFromFile("resourses/images/bb.png");
		t_horse.loadFromFile("resourses/images/bh.png");
		t_rock.loadFromFile("resourses/images/br.png");
	}
	s_queen.setTexture(t_queen);  s_queen.setOrigin(50, 50);
	s_bishop.setTexture(t_bishop);  s_bishop.setOrigin(50, 50);
	s_horse.setTexture(t_horse);  s_horse.setOrigin(50, 50);
	s_rock.setTexture(t_rock);  s_rock.setOrigin(50, 50);
	
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color(80, 80, 80));
	shape.setOutlineThickness(3);
	shape.setOutlineColor(sf::Color::Black);
	shape.setSize(sf::Vector2f(400, 100));
	shape.setOrigin(200, 50);
	shape.setPosition(400, 400);

	s_queen.setPosition(shape.getGlobalBounds().left + 50, shape.getGlobalBounds().top + 50);
	s_bishop.setPosition(shape.getGlobalBounds().left + 150, shape.getGlobalBounds().top + 50);
	s_horse.setPosition(shape.getGlobalBounds().left + 250, shape.getGlobalBounds().top + 50);
	s_rock.setPosition(shape.getGlobalBounds().left + 350, shape.getGlobalBounds().top + 50);

	game->DrawGame();

	char figure = 'p';

	while (game->m_window.isOpen())
	{
		if (game->m_window.pollEvent(game->m_event))
		{
			if (game->m_event.type == sf::Event::Closed)
				game->m_window.close();

			if (game->m_event.type == sf::Event::MouseButtonReleased)
			{
				if (game->m_event.key.code == sf::Mouse::Left)
				{
					if (figure != 'p')
					{
						game->m_window.clear(sf::Color::White);
						game->m_dataPacket.m_pawnUp = figure;
						return figure;
					}
				}
			}
		}

		s_queen.setScale(1, 1);
		s_bishop.setScale(1, 1);
		s_horse.setScale(1, 1);
		s_rock.setScale(1, 1);
		figure = 'p';
		
		if (sf::IntRect(s_queen.getGlobalBounds()).contains(sf::Mouse::getPosition(game->m_window)))
		{
			s_queen.setScale(1.1, 1.1);
			figure = 'q';
		}
		else if (sf::IntRect(s_bishop.getGlobalBounds()).contains(sf::Mouse::getPosition(game->m_window)))
		{
			s_bishop.setScale(1.1, 1.1);
			figure = 'b';
		}
		else if (sf::IntRect(s_horse.getGlobalBounds()).contains(sf::Mouse::getPosition(game->m_window)))
		{
			s_horse.setScale(1.1, 1.1);
			figure = 'h';
		}
		else if (sf::IntRect(s_rock.getGlobalBounds()).contains(sf::Mouse::getPosition(game->m_window)))
		{
			s_rock.setScale(1.1, 1.1);
			figure = 'r';
		}

		game->m_window.draw(shape);
		game->m_window.draw(s_queen);
		game->m_window.draw(s_bishop);
		game->m_window.draw(s_horse);
		game->m_window.draw(s_rock);

		game->m_window.display();
	}

	return figure;
}
