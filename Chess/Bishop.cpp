#include "Bishop.h"

Bishop::Bishop(sf::Vector2i&& pos, char&& color) noexcept : ChessFigure(std::move(pos), std::move(color))
{
	if (m_color == 'w')
		m_texture.loadFromFile("resourses/images/wb.png");
	else if (m_color == 'b')
		m_texture.loadFromFile("resourses/images/bb.png");

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
}

std::vector<sf::Vector2i> Bishop::CanMove() const
{
	return std::vector<sf::Vector2i>();
}
