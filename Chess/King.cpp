#include "King.h"

King::King(sf::Vector2i&& pos, char&& color) noexcept : ChessFigure(std::move(pos), std::move(color))
{
	if (m_color == 'w')
		m_texture.loadFromFile("resourses/images/wk.png");
	else if (m_color == 'b')
		m_texture.loadFromFile("resourses/images/bk.png");

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
}

//bool King::Move()
//{
//	return false;
//}

std::vector<sf::Vector2i> King::CanMove() const
{
	return std::vector<sf::Vector2i>();
}
