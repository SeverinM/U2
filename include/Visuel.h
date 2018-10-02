#ifndef VISUEL_H
#define VISUEL_H
#include <windows.h>
#include <map>

using namespace std;

class Visuel
{
    public:
        enum Couleur{
            Transparent,
            Bleu,
            Vert,
            Cyan,
            Rouge,
            Violet,
            Jaune,
            Blanc,
            Gris,
            BleuClair,
            VertClair,
            CyanClair,
            RougeClair,
            VioletClair,
            JauneClair,
            BlancClair,
            GrisClair
        };
        Visuel();
        map<pair<int, int> , CHAR_INFO *> getPositions();
        void addValue(int x , int y , CHAR_INFO * char_win);
        void deleteValue(int x, int y);
        static int getColor(Couleur devant , Couleur derriere)
        {
            int output(0);
            output = devant + (derriere * 16);
            return output;
        }

    private:
        //Chaque pair represente le couple Position X / Position Y
        map<pair<int, int>, CHAR_INFO *> positions;
};

#endif // VISUEL_H
