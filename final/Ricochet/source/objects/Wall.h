#ifndef WALL_H
#define WALL_H

#include "general.h"
#include "Obstacle.h"

class Wall : public Obstacle
{
    public:
        Wall();
        virtual ~Wall();

    public:
        virtual void onUpdate();
        virtual void onDraw();

};

#endif // WALL_H
