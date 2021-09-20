#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "map.h"
#include "search.h"

// #define TESTGOAL

using namespace std;

int main(int argc, char *argv[])
{
    // Check Command Line Arguments
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " sokoban_test_file"
             << "\n";
        return 1;
    }

    // Open sokoban file
    ifstream sokobanFile(argv[1]);
    if (!sokobanFile)
    {
        cerr << "Error: " << argv[1] << " could not be opened"
             << "\n";
        return 2;
    }

    // Initial State
    Map initialMap(sokobanFile);

#ifdef TESTGOAL

    // ! This'll have to go into a new file .. like a factory
    // initialMap.moveIsLegal(0);
    // initialMap.moveIsLegal(1);
    // initialMap.moveIsLegal(2);
    // initialMap.moveIsLegal(3);

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
    initialMap.moveBlock(1, 2);
    initialMap.moveBlock(1, 3);
    initialMap.moveBlock(1, 3);
    initialMap.moveBlock(1, 3);
    initialMap.moveBlock(1, 0);
    initialMap.moveBlock(1, 0);
    initialMap.moveBlock(2, 3);
    initialMap.moveBlock(2, 2);
    cout << "test-state-3. Goal complete = " << initialMap.goalReached() << endl;

#endif // TESTGOAL
    return 0;
}
