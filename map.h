#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <fstream>
#include <functional>
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
    std::string uniqKey;

public:
    // construct root state from a map file input
    Map(std::ifstream &mapFile);

    // constructor for child states
    Map(Map *rhs, int dir);

    // initialize map spaces from inputstate
    void initState(std::ifstream &mapFile);

    bool operator==(const Map &rhs);
    void printMap();
    long long getKey() const { return stoll(uniqKey); }
    Position getRobot() const { return robot; }
    int getDirectionFromParent() { return directionFromParent; }
    Map *getParent() { return parent; }

    // find legal moves to next state
    // receives 0 - 3; u, r, d, left
    Map *findNextStateFromDirection(const unsigned int dir);
    bool pushBlockIsLegal(const Position);
    bool cannotMove(std::vector<Position> obs, Position pot);
    void moveRobot(unsigned int dir);
    void moveBlock(int index, unsigned int dir);
    bool goalReached();
    void keyGenerator();
    // ! Destructor?
};

// custom hash function (functor) for map
// class map_hash
// {
// public:
//     std::size_t operator()(const Map &m) const
//     {
//         long int hash = stol(m.getKey());
//         return hash;
//     }
// };

#endif // MAP_H
