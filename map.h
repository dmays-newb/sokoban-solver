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

    int sumOfDistances;
    int movesToGetHere;
    int directionFromParent;
    Map *parent;

    std::vector<Position> blocks;
    Position robot;
    std::string uniqKey;

public:
    Map(std::ifstream &mapFile);
    Map(Map *rhs, int dir);
    void initState(std::ifstream &mapFile);
    bool operator==(const Map &rhs);
    void printMap();
    long long getKey() const { return stoll(uniqKey); }
    Position getRobot() const { return robot; }
    int getDirectionFromParent() { return directionFromParent; }
    Map *getParent() { return parent; }
    const int getSumOfDistances() { return sumOfDistances; }
    Map *findNextStateFromDirection(const unsigned int dir);
    bool pushBlockIsLegal(const Position) const;
    bool cannotMove(std::vector<Position> obs, Position pot) const;
    void moveRobot(unsigned int dir);
    void moveBlock(int index, unsigned int dir);
    bool goalReached() const;
    void keyGenerator();
    std::string backTrack();
    void sumDistances();
    void improvedSum();
    int findCornerBlocks() const;
    bool wallPresent(int, int) const;
    bool storagePresent(Position) const;
    void incrementMoves() { movesToGetHere++; }
    int getMoves() { return movesToGetHere; }
    void astarSum();
};

#endif // MAP_H
