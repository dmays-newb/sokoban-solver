#include "position.h"

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