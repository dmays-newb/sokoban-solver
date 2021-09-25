#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
#include "map.h"
#include "position.h"

struct aStarHeuristic
{
    bool operator()(Map *a, Map *b) const
    {
        return (a->getSumOfDistances() > b->getSumOfDistances());
    }
};

class ASTAR
{
private:
    std::unordered_map<long, Map *> closedList;
    std::priority_queue<Map *, std::vector<Map *>, aStarHeuristic> frontier;
    std::string solutionPath;

public:
    ASTAR(Map &root);
    std::string expand();
};

#endif // !ASTAR