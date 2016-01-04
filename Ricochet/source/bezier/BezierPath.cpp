#include "BezierPath.h"

BezierPath::BezierPath()
{
    //ctor
}

BezierPath::~BezierPath()
{
    //dtor
}

double BezierPath::normalise(double number)
{
    if (number >= 2) number -= static_cast<int>(number) - 1;
    if (number > 1)  --number;

    return number;
}

Vector2 BezierPath::getPoint(double t)
{
    double  t_range = 1.0 / getCurveCount();
    int     curve_index = static_cast<int>(t / t_range);
    curve_index = min(curve_index,getCurveCount()-1);
    double  new_t = (t * getCurveCount()) - curve_index;

    return getPoint(new_t,curve_index);
}

Vector2 BezierPath::getPoint(double t, int n)
{
    double u = 1.f-t;
    double tt = t*t;
    double uu = u*u;
    double ttt = tt*t;
    double uuu = uu*u;

    Vector2 p1 = points.at(n).p;
    Vector2 p2 = points.at(n).h2;
    Vector2 p3 = points.at(n+1).h1;
    Vector2 p4 = points.at(n+1).p;

    Vector2 point = p1 * uuu;  // start point
    point += p2 * t * uu * 3;   // control point 1
    point += p3 * tt * u * 3;   // control point 2
    point += p4 * ttt;          // end point

    return point;
}

int BezierPath::getCurveCount()
{
    return points.size()-1;
}

Vector2 BezierPath::findPoint(Vector2 pos, double distance)
{
    for (int i = points.size() -1; i >= 0; --i)
    {
        Vector2 d0 = pos - points.at(i).p;
        Vector2 d1 = pos - points.at(i).h1;
        Vector2 d2 = pos - points.at(i).h2;

        if      (d2.getMagnitude() < distance) return Vector2(i,2);
        else if (d1.getMagnitude() < distance) return Vector2(i,1);
        else if (d0.getMagnitude() < distance) return Vector2(i,0);
    }

    return Vector2(-1,0);
}

Vector2 BezierPath::findPoint(double x, double y, double distance)
{
   return findPoint(Vector2(x,y),distance);
}








