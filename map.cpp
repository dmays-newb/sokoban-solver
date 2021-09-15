#include "map.h"
#include <algorithm>
// #define DEBUG
// #define DEBUG_READ

using namespace std;

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
    for (unsigned int i = 0; i <= mapHeight; i++)
    {
        for (unsigned int j = 0; j <= mapWidth; j++)
        {
            pos.setY(i);
            pos.setX(j);
            current = mapFile.get();
            switch (current)
            {
            case 'O':
                walls.push_back(pos);
                break;
            case 'B':
                blocks.push_back(pos);
                break;
            case 'S':
                storage.push_back(pos);
                break;
            case 'R':
                robot = pos;
                break;
            default:
                break;
            }
        }
    }
    sort(blocks.begin(), blocks.end());
    sort(storage.begin(), storage.end());
}

Map::Map(const Map *rhs)
{
    mapWidth = rhs->mapWidth;
    mapHeight = rhs->mapWidth;
    walls = rhs->walls;
    blocks = rhs->blocks;
    storage = rhs->storage;
    robot = rhs->robot;
}

Map::Map(ifstream &mapFile)
{
    int width = 0, height = 0;
    getMapDimensions(mapFile, width, height);
    mapWidth = width;
    mapHeight = height;

    // Need to get back to beginning of file
    mapFile.clear();
    mapFile.seekg(0);

    // ! Get Char for Each Space of State
    initState(mapFile);

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
    if (!(robot == rhs.robot))
        return false;
    return (equal(blocks.begin(), blocks.end(), rhs.blocks.begin(), rhs.blocks.end()));
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
}

bool Map::moveIsLegal(const unsigned int dir)
{
    // 0 - 3: up, right, down, left directions
    Position potentialMove(robot, dir);
    // cout << "Robot Position: " << robot.getX() << ',' << robot.getY() << '-'
    //  << "Potential move position" << potentialMove.getX() << ',' << potentialMove.getY() << endl;

    if (cannotMove(walls, potentialMove))
    {
        // cout << "Can't move into wall" << endl;
        return false;
    }
    if (cannotMove(blocks, potentialMove))
    {
        Position potentialBlockMove(potentialMove, dir);

        auto it = find(blocks.begin(), blocks.end(), potentialMove);
        int blockIndex = it - blocks.begin();

        cout << "Potential Block Move Position: " << potentialBlockMove.getX() << ',' << potentialBlockMove.getY() << endl;
        if (pushBlockIsLegal(potentialBlockMove))
        {
            cout << "Can move block" << endl;
            // ! Perform move and create new state
            // Create new map using copy constructor
            // potentialBlockMove + dir  OR send index plux direction
            // !mapCopy.moveBlock(int indexOfBlock, dir)
            // ! utilize movePlayer(dir) too
            // block which is equal to potentialBlockMove
            // move according to dir
            // dont forget to move robot
            return true;
        }
        cout << "Cant move block" << endl;
        return false;
    }
    cout << "----------------------" << '\n'
         << "can move into space. "
         << "direction #: " << dir
         << ". Robot Original Position: ";
    this->robot.print();
    cout << endl;
    Map newMap = new Map(*this);
    newMap.moveRobot(dir);
    newMap.printMap();
    return true;
}

void Map::moveRobot(unsigned int dir)
{
    Position newPosition(robot, dir);
    robot.setX(newPosition.getX());
    robot.setY(newPosition.getY());
}

//! Test
void Map::moveBlock(int index, unsigned int dir)
{
    Position newPosition(blocks[index], dir);
    blocks[index].setX(newPosition.getX());
    blocks[index].setY(newPosition.getY());
}