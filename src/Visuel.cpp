#include "../include/Visuel.h"

map<pair<int, int>, CHAR_INFO *>& Visuel::getPositions()
{
    return positions;
};

void Visuel::addValue(int x, int y , CHAR_INFO * char_win)
{
    pair<int, int> pos(x,y);
    positions[pos] = char_win;
};

void Visuel::deleteValue(int x, int y)
{
    pair<int, int> pos(x,y);
    if (positions.find(pos) != positions.end())
    {
        positions.erase(positions.find(pos));
    }
};

Visuel::Visuel(){
}
