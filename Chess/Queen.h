#pragma once
#include "ChessFigure.h"
class Queen :
    public ChessFigure
{
public:
    Queen(sf::Vector2i&& pos, char&& color) noexcept;
    std::vector<sf::Vector2i> CanMove() const override;
};

