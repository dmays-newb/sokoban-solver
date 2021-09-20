#include <iostream>
#include <unordered_map>
#include <string>
#include "map.h"

// ? Clean up maps on heap

// ! Hashtable for Closed-List
// Need to define hash function based on key..

int hash_function(std::string key);

std::unordered_map<std::string, Map *, int>;

// ! Queue for Fronteir