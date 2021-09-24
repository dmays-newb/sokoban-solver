#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include "map.h"

// ? Clean up maps on heap

class GREEDY_SEARCH
{
private:
    std::unordered_map<long, Map *> closedList;
    std::queue<Map *> frontier;
    std::string solutionPath;

public:
    GREEDY_SEARCH(Map &root);
    std::string expand();
};