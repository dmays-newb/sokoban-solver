#include "map.h"
#define DEBUG
#define DEBUG_READ

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

void Map::printMapFromObject()
{
    // ! Define
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
