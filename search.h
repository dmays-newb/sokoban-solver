#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include "map.h"

// ? Clean up maps on heap

class Search
{
private:
    std::unordered_map<long, Map *> closedList;
    std::queue<Map *> frontier;
    std::string solutionPath;

public:
    Search(Map &root);
    std::string expand();
};