#include "Queen.h"

Queen::Queen(sf::Vector2i&& pos, char&& color) noexcept : ChessFigure(std::move(pos), std::move(color))
{
	if (m_color == 'w')
		m_texture.loadFromFile("resourses/images/wq.png");
	else if (m_color == 'b')
		m_texture.loadFromFile("resourses/images/bq.png");

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
}

std::vector<sf::Vector2i> Queen::CanMove() const
{
	return std::vector<sf::Vector2i>();
}
