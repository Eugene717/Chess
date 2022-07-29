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
    bool Move() override;
    bool MoveMP();
};

