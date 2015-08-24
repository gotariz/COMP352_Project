#ifndef TRAIL_H
#define TRAIL_H

#include "general.h"
#include "system/GameData.h"

class Trail
{
    public:
        Trail(){}
        virtual ~Trail(){}

        void addPoint(Vector2 point);
        void addPoint(float x, float y);

        void draw();

        void setPlayerPosition(Vector2 position);
        void setPlayerPosition(float x, float y);

        void clearTrail();

    private:
        void setApart(Vector2 &l, Vector2 &r, float distance);

        Vector2 player;
        vector<Vector2> points;
};

#endif // TRAIL_H
