#ifndef VISUEL_H
#define VISUEL_H
#include <windows.h>
#include <map>
#include <fstream>
#include <string>
#include <memory>

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
        Visuel(int colorD = Visuel::getColor(Couleur::Cyan,Couleur::Transparent));
        map<pair<int, int> , CHAR_INFO *>& getPositions();
        void addValue(int &x , int &y , CHAR_INFO * char_win);
        void deleteValue(int &x, int &y);
        static int getColor(Couleur devant , Couleur derriere)
        {
            int output(0);
            output = devant + (derriere * 16);
            return output;
        };

        static shared_ptr<Visuel> createFromFile(string &fileName, int color = Visuel::getColor(Couleur::Cyan,Couleur::Transparent))
        {
            ifstream inFile(fileName);
            string line;
            int y(0);
            Visuel * visu = new Visuel(color);
            CHAR_INFO * car;
            while (getline(inFile,line))
            {
                for (unsigned int x = 0; x < line.length();x++)
                {
                    car = new CHAR_INFO();
                    car->Char.AsciiChar = line[x];
                    car->Attributes = visu->color;
                    if (line[x] != ' ')
                    {
                        int x2(x);
                        int y2(y);
                        visu->addValue(x2,y2,car);
                    }
                }
                y++;
            }
            inFile.close();
            return shared_ptr<Visuel>(visu);
        }

        void setColor(int &newColor);

    private:
        //Chaque pair represente le couple Position X / Position Y
        map<pair<int, int>, CHAR_INFO *> positions;
        int color;
};

#endif // VISUEL_H
