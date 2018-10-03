#ifndef VISUEL_H
#define VISUEL_H
#include <windows.h>
#include <map>
#include <fstream>
#include <string>
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
        map<pair<int, int> , CHAR_INFO *>& getPositions();
        void addValue(int x , int y , CHAR_INFO * char_win);
        void deleteValue(int x, int y);
        static int getColor(Couleur devant , Couleur derriere)
        {
            int output(0);
            output = devant + (derriere * 16);
            return output;
        };

        static Visuel * createFromFile(string fileName)
        {
            ifstream inFile(fileName);
            string line;
            int y(0);
            Visuel * visu = new Visuel();
            CHAR_INFO * car;
            while (getline(inFile,line))
            {
                for (int x = 0; x < line.length();x++)
                {
                    car = new CHAR_INFO();
                    car->Char.AsciiChar = line[x];
                    car->Attributes = Visuel::getColor(Couleur::Cyan, Couleur::Gris);
                    if (line[x] != ' ')
                    {
                        visu->addValue(x,y,car);
                    }
                }
                y++;
            }
            return visu;
        }

    private:
        //Chaque pair represente le couple Position X / Position Y
        map<pair<int, int>, CHAR_INFO *> positions;
};

#endif // VISUEL_H
