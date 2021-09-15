#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "position.h"

class Map
{
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
    Map(const Map *rhs);

    bool operator==(const Map &rhs);
    void printMap();

    // initialize map from inputstate
    void initState(std::ifstream &mapFile);

    // find legal moves to next state
    // receives 0 - 3; u, r, d, left
    bool moveIsLegal(const unsigned int dir);
    bool pushBlockIsLegal(const Position);
    bool cannotMove(std::vector<Position> obs, Position pot);
    Position getRobot() { return robot; }
    void moveRobot(unsigned int dir);
    void moveBlock(int index, unsigned int dir);

    // ! change moveIsLegal to attempt move?
    // ? return a map

    // ! Check for goal attainment
    // Does blocks... equal storage?? What if there are more blocks than storage..
};

#endif // MAP_H