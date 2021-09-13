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
    //Map(Map mapToCopy);

    // initialize map from inputstate
    void initState(std::ifstream &mapFile);

    // print out map for testing
    void printMapFromObject();
};

#endif // MAP_H