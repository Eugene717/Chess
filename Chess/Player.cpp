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

		m_figures.push_back(new Queen(sf::Vector2i(4, 7), 'w'));
		m_figures.push_back(new King(sf::Vector2i(3, 7), 'w'));
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

char Player::GetColor() const
{
	return m_color;
}