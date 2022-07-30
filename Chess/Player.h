#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class ChessFigure;

class Player :public sf::Drawable
{
	char m_color;
protected:
	std::vector<ChessFigure*> m_figures;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Player(char&& color);
	~Player();

	bool DeleteKilled();
	bool KingKilled();
	char PawnUp();
	char GetColor() const;
	virtual bool Move() = 0;
};
