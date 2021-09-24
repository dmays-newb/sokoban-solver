#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "map.h"
#include "bf_search.h"
#include "df_search.h"
#include "greedy_search.h"

// #define TESTGOAL
// #define HASHTEST

using namespace std;

int main(int argc, char *argv[])
{
    // Check Command Line Arguments
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " sokoban_test_file"
             << "\n";
        return 1;
    }

    // Get Search Type
    string algorithInput = argv[1];

    // Open sokoban file
    ifstream sokobanFile(argv[2]);
    if (!sokobanFile)
    {
        cerr << "Error: " << argv[2] << " could not be opened"
             << "\n";
        return 2;
    }

    Map initialMap(sokobanFile);
    std::string solution;

    if (algorithInput == "bfs")
    {
        BF_SEARCH findSolution(initialMap);
        solution = findSolution.expand();
    }
    else if (algorithInput == "dfs")
    {
        DF_SEARCH findSolution(initialMap);
        solution = findSolution.expand();
    }
    else if (algorithInput == "greedy")
    {
        GREEDY_SEARCH findSolution(initialMap);
        solution = findSolution.expand();
    }

    // Initial State
    cout << "Potential Solution: " << solution << endl;

#ifdef TESTGOAL

    // ! This'll have to go into a new file .. like a factory
    initialMap.findNextStateFromDirection(0);
    initialMap.findNextStateFromDirection(1);
    initialMap.findNextStateFromDirection(2);
    initialMap.findNextStateFromDirection(3);

    // Test Completion
    initialMap.printMap();

    // Test Completion of test-state-1
    // initialMap.moveBlock(0, 3);
    // initialMap.moveBlock(0, 3);
    // initialMap.moveBlock(0, 3);
    // cout << "test-state-1. Goal complete = " << initialMap.goalReached() << endl;

    // Test Completion of test-state-2
    // initialMap.moveBlock(0, 0);
    // initialMap.moveBlock(0, 1);
    // cout << "test-state-2. Goal complete = " << initialMap.goalReached() << endl;

    // Test Completion of test-state-3
    // initialMap.moveBlock(1, 2);
    // initialMap.moveBlock(1, 3);
    // initialMap.moveBlock(1, 3);
    // initialMap.moveBlock(1, 3);
    // initialMap.moveBlock(1, 0);
    // initialMap.moveBlock(1, 0);
    // initialMap.moveBlock(2, 3);
    // initialMap.moveBlock(2, 2);
    // cout << "test-state-3. Goal complete = " << initialMap.goalReached() << endl;

#endif // TESTGOAL

#ifdef HASHTEST
    map_hash hashIt;
    cout << "Map Hash: " << hashIt(initialMap) << endl;
#endif // HASHTEST

    return 0;
}
