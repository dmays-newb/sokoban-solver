#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "map.h"
#include "bf_search.h"
#include "df_search.h"
#include "greedy_search.h"
#include "greedy_plus.h"
#include "astar.h"
using namespace std;

/*
* Formats a final output of moves and count
*/
void finalOutput(std::string input)
{
    cout << "Solution Computed. Here are the moves: ";
    int count = 0;
    int temp;
    char tempChar;
    for (int i = input.length() - 1; i >= 0; i--)
    {
        count++;
        tempChar = input[i];
        temp = tempChar - '0';
        switch (temp)
        {
        case 0:
            cout << "Up";
            break;
        case 1:
            cout << "Right";
            break;
        case 2:
            cout << "Down";
            break;
        case 3:
            cout << "Left";
            break;
        default:
            break;
        }

        if (i != 0)
            cout << ", ";
        if (i % 15 == 0)
            cout << '\n';
    }
    cout << "\nTotal Moves: " << count << endl;
}

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
    else if (algorithInput == "greedy_plus")
    {
        GREEDY_PLUS findSolution(initialMap);
        solution = findSolution.expand();
    }
    else if (algorithInput == "astar")
    {
        ASTAR findSolution(initialMap);
        solution = findSolution.expand();
    }
    else
        cout << algorithInput << " does not match available algorithm types. Please try again." << endl;

    finalOutput(solution);

    return 0;
}
