#include "search.h"
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int hash_function(string key)
{
    stringstream keyInt(key);
    int hash = 0;
    keyInt >> hash;

    //mid-square method for hashing an int
    hash = hash * hash;
}