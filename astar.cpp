#include "astar.h"
#include "map.h"
#include <string>
#include <chrono>

using namespace std;

ASTAR::ASTAR(Map &root)
{
    frontier.push(&root);
    solutionPath = "";
}

string ASTAR::expand()
{
    auto t1 = chrono::high_resolution_clock::now();
    Map *parent, *temp = nullptr;
    while ((temp == nullptr) || !(temp->goalReached()))
    {
        parent = frontier.top();
        frontier.pop();
        closedList.emplace(parent->getKey(), parent);
        for (int i = 0; i < 4; i++)
        {
            // check each direction
            // get nullptr if move ins't legal
            temp = parent->findNextStateFromDirection(i);
            if (temp != nullptr)
            {
                if (!(closedList.contains(temp->getKey())))
                {
                    if (temp->goalReached())
                        break;
                    temp->astarSum();
                    frontier.push(temp);
                }
            }
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    cout << "A* Algorithm took " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
         << " milliseconds\n";

    return temp->backTrack();
}
