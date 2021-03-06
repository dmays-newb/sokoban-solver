#ifndef GREEDYSEARCH_H_INCLUDED
#define GREEDYSEARCH_H_INCLUDED

#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
#include "map.h"
#include "position.h"

struct Heuristic
{
    bool operator()(Map *a, Map *b) const
    {
        return (a->getSumOfDistances() > b->getSumOfDistances());
    }
};

class GREEDY_SEARCH
{
private:
    std::unordered_map<long, Map *> closedList;
    std::priority_queue<Map *, std::vector<Map *>, Heuristic> frontier;
    std::string solutionPath;

public:
    GREEDY_SEARCH(Map &root);
    std::string expand();
};

#endif // !GREEDYSEARCH_H_INCLUDED