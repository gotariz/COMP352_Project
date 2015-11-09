#ifndef LOOPINTERPOLATOR_H
#define LOOPINTERPOLATOR_H

#include "general.h"

class LoopInterpolator
{
    public:
        LoopInterpolator();
        virtual ~LoopInterpolator();

        void setTime(float t);
        void setValue1(float v1);
        void setValue2(float v2);
        void setDuration(float d);
        void setDirection(int d);

        float getTime();
        float getValue1();
        float getValue2();
        float getDuration();
        int getDirection();

        float getValue();

        void update(float elapsedTime);

    protected:
        float time = 0;

        int dir = 1;
        float dur = 0;

        float value = 0;

        float val1 = 0;
        float val2 = 0;
};

#endif // LOOPINTERPOLATOR_H
