#pragma once
#include "ChessFigure.h"
class Horse :
    public ChessFigure
{
public:
    Horse(sf::Vector2i&& pos, char&& color) noexcept;
    std::vector<sf::Vector2i> CanMove() const override;
};

