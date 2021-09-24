#include "greedy_search.h"
#include "map.h"
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

GREEDY_SEARCH::GREEDY_SEARCH(Map &root)
{
    frontier.push(&root);
    solutionPath = "";
}

string GREEDY_SEARCH::expand()
{
    Map *parent, *temp = nullptr;
    while ((temp == nullptr) || !(temp->goalReached()))
    {
        parent = frontier.front();
        frontier.pop();
        for (int i = 0; i < 4; i++)
        {
            // check each direction
            // get nullptr if move ins't legal
            temp = parent->findNextStateFromDirection(i);
            if (temp != nullptr)
            {
                if (!(closedList.contains(temp->getKey())))
                {
                    closedList.emplace(temp->getKey(), temp);
                    frontier.push(temp);
                    if (temp->goalReached())
                        break;
                }
            }
        }
    }

    // return something when temp has reached goal
    return temp->backTrack();
}
