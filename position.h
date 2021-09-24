#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED
#include <fstream>
#include <iostream>

class Position
{
private:
    unsigned int x;
    unsigned int y;

public:
    Position();
    // Takes direction input and creates new position
    Position(const Position &in, const unsigned int dir);
    unsigned int getX() { return x; }
    unsigned int getY() { return y; }
    void setX(unsigned int in) { x = in; }
    void setY(unsigned int in) { y = in; }
    bool operator==(const Position &rhs);
    bool operator<(const Position &rhs);
    void print();
    unsigned int position_hash();
    int distanceFrom(const Position &rhs);
};

inline Position::Position()
{
    x = 0;
    y = 0;
}

inline bool Position::operator==(const Position &rhs)
{
    if (x == rhs.x && y == rhs.y)
        return true;
    return false;
}

// Compare x's and then y's
inline bool Position::operator<(const Position &rhs)
{
    if (x < rhs.x)
        return true;
    if (x == rhs.x)
    {
        if (y < rhs.y)
            return true;
    }
    return false;
}

inline void Position::print()
{
    std::cout << '{' << x << ',' << y << '}';
}

#endif // POSITION_H