#include "AI.h"

AI::AI(char&& color) : Player(std::move(color))
{
}

bool AI::Move()
{
	return false;
}
