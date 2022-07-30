#pragma once
#include "Player.h"

class Human :
    public Player
{
    ChessFigure* m_p_moved_figure;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Human(char&& color);
    void PawnChange(const char& figure);
    bool Move() override;
    bool MoveMP();
};

