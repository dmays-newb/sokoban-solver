#include "position.h"
#include <cmath>

// provide the location of the adjacent space
Position::Position(const Position &in, const unsigned int dir)
{
    x = in.x;
    y = in.y;
    switch (dir)
    {
    case 0:
        y--;
        break;
    case 1:
        x++;
        break;
    case 2:
        y++;
        break;
    case 3:
        x--;
        break;
    default:
        break;
    }
}

Position::Position(int xInput, int yInput)
{
    x = xInput;
    y = yInput;
}

unsigned int Position::position_hash()
{
    return (((x + y) * (x + y + 1)) / 2) + y;
}

int Position::distanceFrom(const Position &rhs)
{
    int totalDistance = 0;
    totalDistance += abs(x - rhs.x);
    totalDistance += abs(y - rhs.y);
    return totalDistance;
}