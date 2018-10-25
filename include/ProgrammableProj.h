#ifndef PROGRAMMABLEPROJ_H
#define PROGRAMMABLEPROJ_H
#include <vector>
#include <string>
#include <queue>
#include <istream>
#include <jansson.h>
#include "../tinyexpr.h"
#include "Projectile.h"

class ProgrammableProj : public Projectile
{
    public:
        struct ParamSequence{
            string directionX;
            string directionY;

            //Milliseconds
            int time;
        };
        ProgrammableProj(int posX, int posY, std::pair<double, double> direction, string tag, Positionable * p);
        ProgrammableProj(int posX , int posY , std::pair<double , double> direction);
        void setTag(const char * newValue);
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

        static queue<ParamSequence> readSequence(const char * sequence)
        {
            json_t * allParams = NULL;
            json_t * steps = NULL;

            allParams = json_object_get(allSequences, sequence);
            steps = json_object_get(allParams, "steps");

            size_t index;
            json_t * value = NULL;

            queue<ParamSequence> output;

            ParamSequence param;
            json_array_foreach(steps , index , value)
            {
                param.directionX = json_string_value(json_object_get(value, "x"));
                param.directionY = json_string_value(json_object_get(value, "y"));
                param.time = json_integer_value(json_object_get(value , "time"));
                output.push(param);
            }
            return output;
        }

        double evaluateString (const char * str);
        bool isCyclic;

    protected:
        queue<ParamSequence> sequence;
        queue<ParamSequence> actualSequence;
        ParamSequence currentSequence;
        void update (float time) override;
        double * posXTarget;
        double * posYTarget;

        //Si mis a true , se repete
        float timeSinceBegin;
        float timeSpent;

        static json_t * allSequences;
        static string nameFile;
        te_variable vars[];
};

#endif // PROGRAMMABLEPROJ_H
