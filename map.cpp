#include "map.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

unsigned int Map::mapWidth;
unsigned int Map::mapHeight;
vector<Position> Map::walls;
vector<Position> Map::storage;
std::string Map::rootKey;

void getMapDimensions(ifstream &mapFile, int &w, int &h)
{
    string line;
    while (getline(mapFile, line))
    {
        if (line.size() > w)
            w = line.size();
        h = h + 1;
    }
}

/*
* Print out map from filestream --- TESTING PURPOSES
*/
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

/*
* Assigns wall, storage, block, and robot positions from input filestream
*/
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

/*
* Copy constructor which also takes direction of movement from parent node
*/
Map::Map(Map *rhs, int dir)
{
    blocks = rhs->blocks;
    robot = rhs->robot;
    directionFromParent = dir;
    parent = rhs;
    movesToGetHere = rhs->movesToGetHere;
}

/*
* Copy constructor
*/
Map::Map(const Map &rhs)
{
    blocks = rhs.blocks;
    robot = rhs.robot;
    directionFromParent = -1;
    parent = rhs.parent;
    movesToGetHere = rhs.movesToGetHere;
    uniqKey = rhs.uniqKey;
}

/*
* Constructor which takes input file stream
*/
Map::Map(ifstream &mapFile)
{
    int width = 0, height = 0;
    getMapDimensions(mapFile, width, height);
    mapWidth = width;
    mapHeight = height;
    parent = nullptr;
    int directionFromParent = -1;
    sumOfDistances = 0;
    movesToGetHere = 0;

    // Get back to beginning of file
    mapFile.clear();
    mapFile.seekg(0);

    // Get Char for Each Space of State
    initState(mapFile);

    keyGenerator();
    rootKey = uniqKey;
}

/*
* Checks potential position (pot) against positions (walls or blocks)
*/
bool Map::cannotMove(vector<Position> obs, Position pot) const
{
    for (Position o : obs)
    {
        if (o == pot)
            return true;
    }
    return false;
}

/*
* Checks if there is a wall or another block in the direction of travel of...
*.. the pushed block
*/
bool Map::pushBlockIsLegal(const Position block) const
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

/*
* Prints Map objects attributes -- FOR TESTING PURPOSES
*/
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
    // cout << "Sum of Shortest Distances: " << this->sumDistances() << endl;
}

/*
* Creates a new Map object (state)
* Checks if move is legal
* Makes legal block move and/or robot move
* Returns pointer to new Map object
*/
Map *Map::findNextStateFromDirection(const unsigned int dir)
{

    // 0 - 3: up, right, down, left directions
    Position potentialMove(robot, dir);

    if (cannotMove(walls, potentialMove))
    {
        return nullptr;
    }
    if (cannotMove(blocks, potentialMove))
    {
        Position potentialBlockMove(potentialMove, dir);

        auto it = find(blocks.begin(), blocks.end(), potentialMove);
        int blockIndex = it - blocks.begin();
        if (pushBlockIsLegal(potentialBlockMove))
        {
            int dirToChild = (int)dir;
            Map *newMap = new Map(this, dirToChild);
            newMap->moveBlock(blockIndex, dir);
            newMap->keyGenerator();
            return newMap;
        }
        return nullptr;
    }
    int dirToChild = (int)dir;
    Map *newMap = new Map(this, dirToChild);
    newMap->moveRobot(dir);
    newMap->sumDistances();
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

/*
* Checks current Map's blocks against storage to see if..
* .. all storage are filled
*/
bool Map::goalReached() const
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

/*
* Generates a unique key based on block and robot positions
*/
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

/*
* Produces string of directions (0-3) from solution state back to root
*/
std::string Map::backTrack()
{
    string solutionString = "";
    string tempString;
    Map *current = this;
    while (current->getParent() != nullptr)
    {
        std::stringstream tmp;
        tmp << current->getDirectionFromParent();
        tempString = tmp.str();
        solutionString.append(tempString);
        current = current->getParent();
    }
    return solutionString;
}

/*
* Sums the distance of each block to its closes storage space
* Used as part of Manhattan Heuristic
*/
void Map::sumDistances()
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
    sumOfDistances = sumOfShortDistances;
}

/*
* Sums up the number of blocks in a state which are in a corner
* minus those that are also occupied by storage spaces
* Used for improving on Manhattan Heuristic
*/
int Map::findCornerBlocks() const
{
    int cornerBlockCount = 0;
    int wallBlockCount = 0;
    unsigned int x, y;
    for (Position block : blocks)
    {
        y = block.getY();
        x = block.getX();

        if (!(storagePresent(block)))
        {
            // wall to left of block
            if (wallPresent(x - 1, y))
            {
                // wall present above
                if (wallPresent(x - 1, y - 1))
                {
                    cornerBlockCount++;
                    break;
                }
                // wall present below
                else if (wallPresent(x - 1, y + 1))
                {
                    cornerBlockCount++;
                }
                else
                    wallBlockCount++;
            }
            // wall to right of block
            if (wallPresent(x + 1, y))
            {
                // wall present above
                if (wallPresent(x + 1, y - 1))
                {
                    cornerBlockCount++;
                    break;
                }
                // wall present below
                else if (wallPresent(x + 1, y + 1))
                {
                    cornerBlockCount++;
                }
                else
                    wallBlockCount++;
            }
        }
    }

    int totalBlockCount = 0;
    if (cornerBlockCount >= 1)
        totalBlockCount += 3;

    if (wallBlockCount >= (blocks.size() / 2))
        totalBlockCount += 2;

    return totalBlockCount;
}

/*
* Used for improvement of Manhattan Heuristic for GREEDY_PLUS
*/
void Map::improvedSum()
{
    int forwardSum = 0;
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
        forwardSum += shortestDist;
    }

    sumOfDistances = forwardSum;
    sumOfDistances += findCornerBlocks();
}

bool Map::wallPresent(int x, int y) const
{
    Position pos(x, y);
    for (Position wall : walls)
    {
        if (wall == pos)
            return true;
    }
    return false;
}

bool Map::storagePresent(Position pos) const
{
    for (Position store : storage)
    {
        if (store == pos)
            return true;
    }
    return false;
}
/*
* Used for f(n) calculation for A* search
*/
void Map::astarSum()
{
    improvedSum();
    // sumDistances();

    int depth = 0;
    Map *temp = parent;
    while (temp->uniqKey != rootKey)
    {
        depth++;
        if (temp->parent == nullptr)
            break;
        temp = temp->parent;
    }
    sumOfDistances *= 2;
    depth = (int)(sqrt(depth));
    sumOfDistances += depth;
}