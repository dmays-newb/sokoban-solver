#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Map
{
public:
    struct Position
    {
        unsigned int x;
        unsigned int y;

        Position();
        // Takes direction input and creates new position
        Position(Position in, const unsigned int dir);
        bool isSamePosition(Position in);
    };

private:
    unsigned int mapWidth;
    unsigned int mapHeight;

    std::vector<Position> walls;
    std::vector<Position> blocks;
    std::vector<Position> storage;
    Position robot;

public:
    // construct a map from a map file input
    Map(std::ifstream &mapFile);

    // copy construct + direction?
    //Map(Map mapToCopy, const unsigned int dir);

    // initialize map from inputstate
    void initState(std::ifstream &mapFile);

    // find legal moves to next state
    // receives 0 - 3; u, r, d, left

    bool objectCollides(std::vector<Position> obs, Position pot);
    bool moveIsLegal(const unsigned int dir);
    bool moveBlockLegal(const Position);
};

inline Map::Position::Position()
{
    x = 0;
    y = 0;
}

inline bool Map::Position::isSamePosition(Position in)
{
    if (x == in.x && y == in.y)
        return true;
    return false;
}

#endif // MAP_H