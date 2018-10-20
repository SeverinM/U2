#ifndef PROGRAMMABLEPROJ_H
#define PROGRAMMABLEPROJ_H
#include "Projectile.h"
#include <vector>
#include <string>
#include <queue>
#include <istream>
#include <jansson.h>

struct ParamSequence
{
    string directionX;
    string directionY;

    //Milliseconds
    int time;
};

class ProgrammableProj : public Projectile
{
    public:
        ProgrammableProj(int posX, int posY, std::pair<double, double> direction, string tag);
        void setTag(string &newValue);

        static void initSequence()
        {
            json_error_t error;
            string line;
            string jsonFile;
            ifstream file(nameFile);

            if (file.is_open())
            {
                while(getline(file, line))
                {
                    jsonFile += line;
                }
                file.close();
            }
            allSequences = json_loads(jsonFile.c_str(), 0 , &error);
        }

        static queue<ParamSequence> readSequence(char * sequence)
        {
            queue <ParamSequence> output;
            json_t * allParams;
            json_t * steps;

            allParams = json_object_get(allSequences, sequence);
            steps = json_object_get(allParams, "steps");

            size_t index;
            json_t * value;
            json_t * valueStep;
            json_t * xKey;
            json_t * yKey;
            json_t * timeKey;

            ParamSequence param;
            json_array_foreach(steps , index , value)
            {
                xKey = json_object_get(value, "x");
                yKey = json_object_get(value, "y");
                timeKey = json_object_get(value , "time");

                param.directionX = json_string_value(xKey);
                param.directionY = json_string_value(yKey);
                param.time = json_integer_value(timeKey);
            }

            return output;
        }

        static float evaluateString (const char * str)
        {
            return 1;
        }

    protected:
        vector<ParamSequence> sequence;
        queue<ParamSequence> actualSequence;
        virtual void update (float time);

        //Si mis a true , se repete
        bool isCyclic;
        float timeSinceBegin;
        static json_t * allSequences;
        static string nameFile;
};

#endif // PROGRAMMABLEPROJ_H
