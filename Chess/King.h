#pragma once
#include "ChessFigure.h"

class King :
    public ChessFigure
{
public:
    King(sf::Vector2i&& pos, char&& color) noexcept;
    bool Move() override;
    std::vector<sf::Vector2i> CanMove() const override;
};

