#pragma once
#include "ChessFigure.h"
class Rock :
    public ChessFigure
{
public:
    Rock(sf::Vector2i&& pos, char&& color) noexcept;
    std::vector<sf::Vector2i> CanMove() const override;
};

