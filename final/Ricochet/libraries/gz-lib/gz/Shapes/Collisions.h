#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#include "gz/Shapes/Point.h"
#include "gz/Shapes/Rect.h"

namespace gz
{
    template <class T, class T2>
    bool isCollision(Point<T> point, Rect<T2> rec);

    template <class T, class T2>
    inline bool isCollision(Point<T> point, Rect<T2> rec)
    {
        if (point.x < rec.x)                return false;
        if (point.x > (rec.x + rec.w - 1))  return false;
        if (point.y < rec.y)                return false;
        if (point.y > (rec.y + rec.h - 1))  return false;

        return true;
    }
}

#endif // COLLISIONS_H_INCLUDED
