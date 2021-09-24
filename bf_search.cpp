#include "bf_search.h"
#include "map.h"
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

string bf_backTrack(Map *s)
{
    // s->printMap();

    string solutionString = "";
    string tempString;
    Map *current = s;
    while (current != nullptr)
    {
        current->printMap();
        cout << "Current Dir: " << current->getDirectionFromParent() << endl;
        cout << "Robot Position: ";
        current->getRobot().print();
        cout << endl;
        std::stringstream tmp;
        tmp << current->getDirectionFromParent();
        tempString = tmp.str();
        solutionString.append(tempString);
        current = current->getParent();
    }

    return solutionString;
}

BF_SEARCH::BF_SEARCH(Map &root)
{
    frontier.push(&root);
    solutionPath = "";
}

string BF_SEARCH::expand()
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
    return bf_backTrack(temp);
}
