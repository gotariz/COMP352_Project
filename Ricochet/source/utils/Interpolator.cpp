#include "Interpolator.h"

Interpolator::Interpolator()
{
    //ctor
}

Interpolator::~Interpolator()
{
    //dtor
}

void Interpolator::set(Vector2 _p1, Vector2 _p2)
{
    p1 = _p1;
    p2 = _p2;
    d = p2 - p1;
}

void Interpolator::setP1(Vector2 _p1)
{
    p1 = _p1;
    d = p2 - p1;
}

void Interpolator::setP2(Vector2 _p2)
{
    p2 = _p2;
    d = p2 - p1;
}


void Interpolator::reset()
{
    elapsed = 0;
    percent = 0;
}

void Interpolator::update(float delta)
{
    elapsed += delta;
    percent = elapsed / duration;
}

void Interpolator::getPosition()
{
    Vector delta = d;
    delta *= percent;
    return p1 + delta;

}

void Interpolator::getPositionDelta()
{
    Vector2 delta = d;
    delta *= percent;
    return delta;
}
