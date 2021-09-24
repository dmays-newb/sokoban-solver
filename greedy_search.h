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
        // ! Make sure this is comparing in the right direction!
        return (a->sumOfShortestDistances() > b->sumOfShortestDistances());
    }
};

class GREEDY_SEARCH
{
private:
    std::unordered_map<long, Map *> closedList;
    // ! Change to priority queue
    std::priority_queue<Map *, std::vector<Map *>, Heuristic> frontier;
    // std::queue<Map *> frontier;
    std::string solutionPath;

public:
    GREEDY_SEARCH(Map &root);
    std::string expand();
};