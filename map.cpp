#include "map.h"
#include <algorithm>
#include <sstream>
// #define DEBUG
// #define DEBUG_READ

using namespace std;

unsigned int Map::mapWidth;
unsigned int Map::mapHeight;
vector<Position> Map::walls;
vector<Position> Map::storage;

void getMapDimensions(ifstream &mapFile, int &w, int &h)
{
    string line;
    while (getline(mapFile, line))
    {
        if (line.size() > w)
            w = line.size();
        h = h + 1;
    }

#ifdef DEBUG
    cout << "map height: " << h << endl;
    cout << "map width: " << w << endl;
#endif // DEBUG
}

void printMapFromFile(ifstream &mapFile)
{
    string line = "";
    if (mapFile.is_open())
    {
        while (getline(mapFile, line))
        {
            cout << line << endl;
        }
    }
}

void Map::initState(ifstream &mapFile)
{
    char current;
    Position pos;
    bool endOfLine = false;

    for (unsigned int i = 0; i <= mapHeight; i++)
    {
        for (unsigned int j = 0; j <= mapWidth; j++)
        {
            pos.setY(i);
            pos.setX(j);
            current = mapFile.get();

            while (current == '\n' && j <= mapWidth)
            {
                pos.setY(i);
                pos.setX(j);
                Map::walls.push_back(pos);
                j++;
            }

            if (current == '\n')
                break;

            switch (current)
            {
            case 'O':
                Map::walls.push_back(pos);
                break;
            case 'B':
                blocks.push_back(pos);
                break;
            case 'S':
                Map::storage.push_back(pos);
                break;
            case 'R':
                robot = pos;
                break;
            default:
                break;
            }
        }
    }
}

Map::Map(Map *rhs, int dir)
{
    blocks = rhs->blocks;
    robot = rhs->robot;
    directionFromParent = dir;
    parent = rhs;
}

Map::Map(ifstream &mapFile)
{
    int width = 0, height = 0;
    getMapDimensions(mapFile, width, height);
    mapWidth = width;
    mapHeight = height;
    parent = nullptr;
    int directionFromParent = -1;

    // Get back to beginning of file
    mapFile.clear();
    mapFile.seekg(0);

    // Get Char for Each Space of State
    initState(mapFile);

    keyGenerator();

#ifdef DEBUG_READ
    cout << "Walls: ";
    for (Position w : walls)
    {
        cout << w.x << ',' << w.y << "; ";
    }
    cout << endl;

    cout << "Blocks: ";
    for (Position b : blocks)
    {
        cout << b.x << ',' << b.y << "; ";
    }
    cout << endl;

    cout << "Storage: ";
    for (Position s : storage)
    {
        cout << s.x << ',' << s.y << "; ";
    }
    cout << endl;

    cout << "Robot Position: " << robot.x << ',' << robot.y;
#endif // DEBUG
}

// checks potential position (pot) against positions (walls or blocks)
bool Map::cannotMove(vector<Position> obs, Position pot)
{
    for (Position o : obs)
    {
        if (o == pot)
            return true;
    }
    return false;
}

// Checks if there is a wall or another block in the direction of travel of...
// .. the pushed block
bool Map::pushBlockIsLegal(const Position block)
{
    if (cannotMove(walls, block) || cannotMove(blocks, block))
        return false;
    return true;
}

bool Map::operator==(const Map &rhs)
{
    if (uniqKey.compare(rhs.uniqKey) == 0)
        return true;
    return false;
}

void Map::printMap()
{
    cout << "Block Positions" << endl;
    for (Position b : blocks)
    {
        b.print();
    }
    cout << '\n'
         << "Storage Positions" << endl;
    for (Position s : storage)
    {
        s.print();
    }
    cout << endl;
    cout << "Robot Position:";
    robot.print();
    cout << endl;
    cout << "Sum of Shortest Distances: " << this->sumOfShortestDistances() << endl;
}

Map *Map::findNextStateFromDirection(const unsigned int dir)
{

    // 0 - 3: up, right, down, left directions
    Position potentialMove(robot, dir);
    // cout << "Robot Position: " << robot.getX() << ',' << robot.getY() << '-'
    //      << "Potential move position" << potentialMove.getX() << ',' << potentialMove.getY() << endl;

    if (cannotMove(walls, potentialMove))
    {
        // cout << "Can't move into wall" << endl;
        return nullptr;
    }
    if (cannotMove(blocks, potentialMove))
    {
        Position potentialBlockMove(potentialMove, dir);

        auto it = find(blocks.begin(), blocks.end(), potentialMove);
        int blockIndex = it - blocks.begin();

        // cout << "Potential Block Move Position: " << potentialBlockMove.getX() << ',' << potentialBlockMove.getY() << endl;
        if (pushBlockIsLegal(potentialBlockMove))
        {
            // cout << "Can move block" << endl;
            int dirToChild = (int)dir;
            Map *newMap = new Map(this, dirToChild);
            newMap->moveBlock(blockIndex, dir);
            newMap->keyGenerator();
            return newMap;
        }
        // cout << "Cant move block" << endl;
        return nullptr;
    }
    // cout << "----------------------" << '\n'
    //      << "can move into space. "
    //      << "direction #: " << dir
    //      << ". Robot Original Position: ";
    // this->robot.print();
    // cout << endl;
    int dirToChild = (int)dir;
    Map *newMap = new Map(this, dirToChild);
    newMap->moveRobot(dir);
    newMap->keyGenerator();
    return newMap;
}

void Map::moveRobot(unsigned int dir)
{
    Position newPosition(robot, dir);
    robot.setX(newPosition.getX());
    robot.setY(newPosition.getY());
}

void Map::moveBlock(int index, unsigned int dir)
{
    Position newPosition(blocks[index], dir);
    blocks[index].setX(newPosition.getX());
    blocks[index].setY(newPosition.getY());
    moveRobot(dir);
}

bool Map::goalReached()
{
    int matchCount = 0;
    for (Position s : storage)
    {
        for (Position b : blocks)
        {
            if (b == s)
                matchCount++;
        }
    }
    if (matchCount == storage.size())
        return true;
    return false;
}

void Map::keyGenerator()
{
    string key = "";
    sort(blocks.begin(), blocks.end());

    for (Position p : blocks)
    {
        key.append(std::to_string(p.getX()));
        key.append(std::to_string(p.getY()));
    }

    key.append(std::to_string(robot.getX()));
    key.append(std::to_string(robot.getY()));

    uniqKey = key;
}

std::string Map::backTrack()
{
    string solutionString = "";
    string tempString;
    Map *current = this;
    while (current->getParent() != nullptr)
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

int Map::sumOfShortestDistances()
{
    int sumOfShortDistances = 0;
    int shortestDist;
    int temp;
    for (Position block : blocks)
    {
        shortestDist = 10000;
        for (Position storage : storage)
        {
            temp = block.distanceFrom(storage);
            if (temp < shortestDist)
                shortestDist = temp;
        }
        sumOfShortDistances += shortestDist;
    }
    return sumOfShortDistances;
}