#ifndef TEXTE_H
#define TEXTE_H
#include "Positionable.h"


class Texte : public Positionable
{
    public:
        Texte(int startPosX, int startPosY);
        virtual void update(float time);
        virtual typePosable getTypePosable();
        virtual ~Texte();

    protected:

    private:
};

#endif // TEXTE_H
