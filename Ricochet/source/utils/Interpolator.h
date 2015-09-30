#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include"Vector2.h"

class Interpolator
{
    public:
        Interpolator();
        virtual ~Interpolator();

        void reset();

        void set(Vector2 _p1, Vector2 _p2);
        void setP1(Vector2 _p1);
        void setP2(Vector2 _p2);
        void update(float delta);
        Vector2 getPosition();
        Vector2 getPositionDelta();

    public:
        float duration = 0;

    protected:
        float elapsed = 0;
        float percent = 0;

        Vector2 p1;
        Vector2 p2;
        Vector2 d;

};

#endif // INTERPOLATOR_H
