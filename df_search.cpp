#include "df_search.h"
#include "map.h"
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

DF_SEARCH::DF_SEARCH(Map &root)
{
    frontier.push(&root);
    solutionPath = "";
}

string DF_SEARCH::expand()
{
    Map *parent, *temp = nullptr;
    while ((temp == nullptr) || !(temp->goalReached()))
    {
        parent = frontier.top();
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
                    if (temp->goalReached())
                        break;
                    frontier.push(temp);
                }
            }
        }
        closedList.emplace(parent->getKey(), parent);
    }

    return temp->backTrack();
}
