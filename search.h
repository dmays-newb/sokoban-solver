#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include "map.h"

// ? Clean up maps on heap

// ! Hashtable for Closed-List
// Need to define hash function based on key..

// int hash_function(std::string key);

// ! Queue for Fronteir

class search
{
private:
    std::unordered_map<int, Map *> closedList;
    std::queue<Map *> fronteir;
};