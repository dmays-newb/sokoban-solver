#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include "map.h"

// ? Clean up maps on heap

class DF_SEARCH
{
private:
    std::unordered_map<long, Map *> closedList;
    std::stack<Map *> frontier;
    std::string solutionPath;
    Map *root;

public:
    DF_SEARCH(Map &root);
    std::string expand();
};