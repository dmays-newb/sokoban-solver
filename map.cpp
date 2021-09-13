#include "map.h"
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
            pos.y = i;
            pos.x = j;
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
bool Map::objectCollides(vector<Position> obs, Position pot)
{
    for (Position o : obs)
    {
        if (o.isSamePosition(pot))
            return true;
    }
    return false;
}

// Checks if there is a wall or another block in the direction of travel of...
// .. the pushed block
bool Map::moveBlockLegal(const Position block)
{
    if (objectCollides(walls, block) || objectCollides(blocks, block))
        return false;
    return true;
}

// This will provide the location of the adjacent space
// which the robot is attempting to move to .. or check for block
Map::Position::Position(Position in, const unsigned int dir)
{
    x = in.x;
    y = in.y;
    switch (dir)
    {
    case 0:
        y--;
        break;
    case 1:
        x++;
        break;
    case 2:
        y++;
        break;
    case 3:
        x--;
        break;
    default:
        break;
    }
}

bool Map::moveIsLegal(const unsigned int dir)
{
    // 0 - 3: up, right, down, left directions
    Position potentialMove(robot, dir);
    cout << "Robot Position: " << robot.x << ',' << robot.y << '-'
         << "Potential move position" << potentialMove.x << ',' << potentialMove.y << endl;

    if (objectCollides(walls, potentialMove))
    {
        cout << "Can't move into wall" << endl;
        return false;
    }
    if (objectCollides(blocks, potentialMove))
    {
        Position potentialBlockMove(potentialMove, dir);
        cout << "Potential Block Move Position: " << potentialBlockMove.x << ',' << potentialBlockMove.y << endl;
        if (moveBlockLegal(potentialBlockMove))
        {
            cout << "Can move block" << endl;
            // Perform move and create new state!
            return true;
        }
        cout << "Cant move block" << endl;
        return false;
    }
    cout << "can move into space" << endl;
    // Perform move and create new state!
    return true;
}

// ! Add another map with a narrow passage