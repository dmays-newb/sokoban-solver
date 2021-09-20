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
    static unsigned int mapWidth;
    static unsigned int mapHeight;
    static std::vector<Position> walls;
    static std::vector<Position> storage;

    int directionFromParent;
    Map *parent;
    // bool goalState;

    std::vector<Position> blocks;
    Position robot;

    // std::string hash;

public:
    // construct a map from a map file input
    // Test Map!
    Map(std::ifstream &mapFile);
    Map(const Map *rhs, int dir);

    bool operator==(const Map &rhs);
    void printMap();

    // initialize map from inputstate
    void initState(std::ifstream &mapFile);

    // find legal moves to next state
    // receives 0 - 3; u, r, d, left
    Map *findNextStateFromDirection(const unsigned int dir);
    bool pushBlockIsLegal(const Position);
    bool cannotMove(std::vector<Position> obs, Position pot);
    Position getRobot() { return robot; }
    void moveRobot(unsigned int dir);
    void moveBlock(int index, unsigned int dir);
    bool goalReached();
    std::string keyGenerator();
    int mapHashFunction();
    // ! Destructor?
};

class MapHash
{
public:
    std::size_t operator()(const Map &m)
    {
        for (Position p :)
    }
};

#endif // MAP_H