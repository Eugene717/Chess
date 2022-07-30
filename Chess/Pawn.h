#pragma once
#include "ChessFigure.h"

class Queen;
class Bishop;
class Horse;
class Rock;

class Pawn :
    public ChessFigure
{
public:
    Pawn(sf::Vector2i&& pos, char&& color) noexcept;
    std::vector<sf::Vector2i> CanMove() const override;
};

