#ifndef PROGRAMMABLEPROJ_H
#define PROGRAMMABLEPROJ_H
#include "Projectile.h"
#include <vector>
#include <string>
#include <queue>
#include <istream>
#include <jansson.h>
#include "../tinyexpr.h"

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
        ProgrammableProj(int posX, int posY, std::pair<double, double> direction, string tag, Positionable * p);
        ProgrammableProj();
        void setTag(char * &newValue);
        void nextSequence();

        static void initSequences()
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
                output.push(param);
            }

            return output;
        }

        double evaluateString (const char * str);

    protected:
        queue<ParamSequence> sequence;
        queue<ParamSequence> actualSequence;
        ParamSequence currentSequence;
        virtual void update (float time);
        double * posXTarget;
        double * posYTarget;

        //Si mis a true , se repete
        bool isCyclic;
        float timeSinceBegin;
        float timeSpent;

        static json_t * allSequences;
        static string nameFile;
        te_variable vars[];
};

#endif // PROGRAMMABLEPROJ_H
