#include "greedy_search.h"
#include "map.h"
#include <string>
#include <chrono>

using namespace std;

GREEDY_SEARCH::GREEDY_SEARCH(Map &root)
{
    frontier.push(&root);
    solutionPath = "";
}

string GREEDY_SEARCH::expand()
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
                    temp->sumDistances();
                    frontier.push(temp);
                }
            }
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Greedy Algorithm took " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
         << " milliseconds\n";

    // return something when temp has reached goal
    return temp->backTrack();
}
