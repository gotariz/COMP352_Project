#include "Trail.h"

void Trail::addPoint(Vector2 point)
{
    points.push_back(point);
}

void Trail::addPoint(float x, float y)
{
    points.push_back(Vector2(x,y));
}

void Trail::clearTrail()
{
    points.clear();
}

void Trail::draw()
{
    // Trim the tail
    float d = 0;
    Vector2 previous = player;
    for (int i = points.size() - 1; i >= 0; --i)
    {
        Vector2 nv = previous - points.at(i);
        d += nv.getMagnitude();

        if (d > length)
        {
            Vector2 nc = points.at(i) - previous;
            d -= nc.getMagnitude();
            nc.setMagnitude( length - d );
            points.at(i) = previous + nc;

            previous = points.at(i);

            --i;
            while (i  >= 0)
            {
                points.erase(points.begin());
                --i;
            }
        }
        else
        {
            previous = points.at(i);
        }
    }

    vector<gzPair> pairs;
    float dist = 0;
    Vector2 last;
    for (int i = 0; i < points.size(); ++i)
    {
        Vector2 p1 = gdata.toScreenPixels(points.at(i));
        Vector2 p2;

        Vector2 point1 = points.at(i);
        Vector2 point2;


        if (i >= (points.size() - 1))
        {
            p2 = gdata.toScreenPixels(player);
            point2 = player;
        }
        else
        {
            p2 = gdata.toScreenPixels(points.at(i + 1));
            point2 = points.at(i + 1);
        }

        Vector2 left(0,0.5);
        Vector2 right(0,-0.5);
        Vector2 dir = point2 - point1;
        float angle = dir.getAngle();
        left.rotate(angle);
        right.rotate(angle);

        gzPair pair1;
        pair1.left = point1 + left;
        pair1.right = point1 + right;
        pair1.center = point1;

        if (i == 0) last = point1;
        Vector2 line = last - point1;
        dist += line.getMagnitude();
        setApart(pair1.left,pair1.right,(dist / length) * width);
        last = point1;

        pairs.push_back(pair1);

        gzPair pair2;
        pair2.left = point2 + left;
        pair2.right = point2 + right;
        pair2.center = point2;

        Vector2 line2 = last - point2;
        dist += line2.getMagnitude();
        setApart(pair2.left,pair2.right,(dist / length) * width);
        last = point2;

        pairs.push_back(pair2);

//        sf::Vertex dline[] =
//        {
//            sf::Vertex(sf::Vector2f(p1.x, p1.y)),
//            sf::Vertex(sf::Vector2f(p2.x, p2.y))
//        };
//
//        gdata.window->draw(dline, 2, sf::Lines);
    }

    for (int i = pairs.size() - 1; i > 0;i-=1)
    {
        Vector2 p1 = gdata.toPixels(pairs.at(i).left);
        Vector2 p2 = gdata.toPixels(pairs.at(i).right);
        Vector2 p3 = gdata.toPixels(pairs.at(i-1).right);
        Vector2 p4 = gdata.toPixels(pairs.at(i-1).left);

        sf::ConvexShape convex;
        convex.setPointCount(4);
        convex.setPoint(0,sf::Vector2f(p1.x,p1.y));
        convex.setPoint(1,sf::Vector2f(p2.x,p2.y));
        convex.setPoint(2,sf::Vector2f(p3.x,p3.y));
        convex.setPoint(3,sf::Vector2f(p4.x,p4.y));

        convex.setFillColor(sf::Color(255,255,255,64));
        gdata.window->draw(convex);
    }

//    sf::CircleShape circle(2);
//    circle.setOrigin(1,1);
//    for (int i = 0; i < pairs.size(); ++i)
//    {
//        Vector2 p = gdata.toPixels(pairs.at(i).left);
//        circle.setPosition(p.x,p.y);
//        circle.setFillColor(sf::Color::Green);
//        gdata.window->draw(circle);
//
//        p = gdata.toPixels(pairs.at(i).right);
//        circle.setPosition(p.x,p.y);
//        circle.setFillColor(sf::Color::Blue);
//        gdata.window->draw(circle);
//    }
}

void Trail::setPlayerPosition(Vector2 position)
{
    player = position;
}

void Trail::setPlayerPosition(float x, float y)
{
    player.set(x,y);
}

void Trail::setApart(Vector2& l, Vector2& r, float distance)
{
    //if (distance == 0) distance = 0.01;
    // find the center point
    Vector2 center = l + ((r - l) / 2);
    Vector2 ld = l - center;
    Vector2 rd = r - center;
    ld.setMagnitude(distance / 2);
    rd.setMagnitude(distance / 2);
    l = center + ld;
    r = center + rd;
}

