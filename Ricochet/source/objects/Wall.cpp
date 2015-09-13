#include "Wall.h"

Wall::Wall()
{
    //ctor
    m_type = WALL;
}

Wall::~Wall()
{
    //dtor
}

void Wall::onUpdate()
{
    if (m_enabledMovement && m_moving)
    {
        // determine if past destination
        float max_dist  = (m_point2 - m_point1).getMagnitude();
        float p1_dist   = (getAbsolutePosition() - m_point1).getMagnitude();
        float p2_dist   = (getAbsolutePosition() - m_point2).getMagnitude();

        // move back to destination
        if ( p1_dist >= max_dist )
        {
            // we have arrived at or past p2
            setAbsolutePosition(m_point2);
            m_dest = m_point1;
            Vector2 vel = m_point1 - m_point2;
            vel /= m_duration;
            setLinearVelocity(vel);
        }
        else if (p2_dist >= max_dist)
        {
            // we have arrived at or past p1
            setAbsolutePosition(m_point1);
            m_dest = m_point2;
            Vector2 vel = m_point2 - m_point1;
            vel /= m_duration;
            setLinearVelocity(vel);
        }

    }
}

void Wall::onDraw()
{
    if (!m_physicsObject || !m_enabled) return;

    for (b2Fixture* f = m_physicsObject->GetFixtureList(); f; f = f->GetNext())
    {
        b2Shape::Type shapeType = f->GetType();

        if ( shapeType == b2Shape::e_polygon )
        {
            b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
            sf::ConvexShape convex;
            convex.setPointCount(polygonShape->GetVertexCount());

            for (int i = 0; i < polygonShape->GetVertexCount(); ++i)
            {

                Vector2 b2v = polygonShape->GetVertex(i);
                b2v.rotate( getAbsoluteRotation() );
                Vector2 v = getAbsolutePosition() + b2v;

                v = gdata.toScreenPixels(v);
                convex.setPoint(i,sf::Vector2f(v.x,v.y));
            }

            convex.setFillColor(sf::Color::Black);
            gdata.window->draw(convex);

        }
    }

}

