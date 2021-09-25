#ifndef GREEDYPLUS_H_INCLUDED
#define GREEDYPLUS_H_INCLUDED

#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
#include "map.h"
#include "position.h"

struct ImprovedHeuristic
{
    bool operator()(Map *a, Map *b) const
    {
        return (a->getSumOfDistances() > b->getSumOfDistances());
    }
};

class GREEDY_PLUS
{
private:
    std::unordered_map<long, Map *> closedList;
    std::priority_queue<Map *, std::vector<Map *>, ImprovedHeuristic> frontier;
    std::string solutionPath;

public:
    GREEDY_PLUS(Map &root);
    std::string expand();
};

#endif // !GREEDYPLUS