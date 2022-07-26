#pragma once
#include "ChessFigure.h"
class Bishop :
    public ChessFigure
{
public:
    Bishop(sf::Vector2i&& pos, char&& color) noexcept;
    std::vector<sf::Vector2i> CanMove() const override;
};

