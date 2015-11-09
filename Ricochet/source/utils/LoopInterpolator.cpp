#include "LoopInterpolator.h"

LoopInterpolator::LoopInterpolator()
{
    //ctor
}

LoopInterpolator::~LoopInterpolator()
{
    //dtor
}

void LoopInterpolator::setTime(float t)
{
    time = t;
}

void LoopInterpolator::setValue1(float v1)
{
    val1 = v1;
}

void LoopInterpolator::setValue2(float v2)
{
    val2 = v2;
}

void LoopInterpolator::setDirection(int d)
{
    dir = d;
}

void LoopInterpolator::setDuration(float d)
{
    dur = d;
}

float LoopInterpolator::getValue1()
{
    return val1;
}

float LoopInterpolator::getValue2()
{
    return val2;
}

int LoopInterpolator::getDirection()
{
    return dir;
}

float LoopInterpolator::getDuration()
{
    return dur;
}

float LoopInterpolator::getValue()
{
    return value;
}

float LoopInterpolator::getTime()
{
    return time;
}

void LoopInterpolator::update(float elapsedTime)
{
    if (dir > 0)    // increasing
    {
        time += elapsedTime;
        if (time >= dur)
        {
            float excess = time - dur;
            time -= excess;
            dir = -1;
        }
    }
    else            // decreasing
    {
        time -= elapsedTime;
        if (time <= 0)
        {
            time *= -1;
            dir = 1;
        }
    }

    float range = val2 - val1;
    float percent = time / dur;
    value = val1 + (range * percent);
}
