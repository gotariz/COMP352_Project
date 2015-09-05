#ifndef HOLE_H
#define HOLE_H

#include "general.h"
#include "Obstacle.h"
#include "system/AssetManager.h"

class Hole : public Obstacle
{
    public:
        Hole();
        virtual ~Hole();

        virtual void onUpdate();
        virtual void onDraw();
        virtual void onEnterCollision(CollisionData cd);
};

#endif // HOLE_H
