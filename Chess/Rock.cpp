#include "Rock.h"

Rock::Rock(sf::Vector2i&& pos, char&& color) noexcept : ChessFigure(std::move(pos), std::move(color))
{
	if (m_color == 'w')
		m_texture.loadFromFile("resourses/images/wr.png");
	else if (m_color == 'b')
		m_texture.loadFromFile("resourses/images/br.png");

	m_sprite.setTexture(m_texture);

	m_sprite.setPosition(m_pos.x * 100 + 50, m_pos.y * 100 + 50);
}

std::vector<sf::Vector2i> Rock::CanMove() const
{
	return std::vector<sf::Vector2i>();
}
