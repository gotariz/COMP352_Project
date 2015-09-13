#include "Obstacle.h"

Obstacle::Obstacle()
{
    //ctor
}

Obstacle::~Obstacle()
{
    //dtor
}

bool Obstacle::getEnabled()
{
    return m_enabled;
}

bool Obstacle::getEnabledMovement()
{
    return m_enabledMovement;
}

bool Obstacle::getEnabledRotation()
{
    return m_enabledRotation;
}


void Obstacle::enable(bool enable)
{
    m_enabled = enable;
    if (m_physicsObject)
    {
        if (m_enabled)
        {
            b2Fixture* f = m_physicsObject->GetFixtureList();
            while (f)
            {
                b2Filter filter;
                filter.categoryBits = m_colCat;
                filter.maskBits = m_colMask;

                f->SetFilterData(filter);
                f = f->GetNext();
            }
        }
        else
        {
            b2Fixture* f = m_physicsObject->GetFixtureList();
            while (f)
            {
                m_colCat = f->GetFilterData().categoryBits;
                m_colMask = f->GetFilterData().maskBits;

                b2Filter filter;
                filter.categoryBits = CF_NONE;
                filter.maskBits = CF_NONE;

                f->SetFilterData(filter);
                f = f->GetNext();
            }
        }

    }
}

void Obstacle::enableMovement(bool enable)
{
    if (enable)
    {
       setLinearVelocity(m_vel) ;
    }
    else
    {
        m_vel = getVelocity();
        setLinearVelocity(Vector2(0,0));
    }

    m_enabledMovement = enable;

}

void Obstacle::enableRotation(bool enable)
{
    if (enable)
    {
       setAngularVelocity(m_rotVel) ;
    }
    else
    {
        m_rotVel = getAngularVelocity();
        setAngularVelocity(0);
    }

    m_enabledRotation = enable;
}

void Obstacle::onUpdate()
{
	if (m_enabledMovement && m_moving)
	{
		Vector2 delta;
		Vector2 dist_v = m_point1 - m_point2;
		float dist = dist_v.getMagnitude();

		delta = m_point2 - m_point1;
		delta.normalise();
		delta.setMagnitude(dist * (m_time / m_duration));

		if (m_dest == m_point1) // time is increasing
		{
			m_time += gdata.m_timeDelta;
			if (m_time >= m_duration)
			{
				m_time = m_duration - (m_time - m_duration);
				m_dest = m_point2;
			}
		}
		else if (m_dest == m_point2)
		{
			m_time -= gdata.m_timeDelta;
			if (m_time <= 0)
			{
				m_time = 0 - m_time;
				m_dest = m_point1;
			}
		}

		setAbsolutePosition(m_point1 + delta);
	}
}

//void Obstacle::onDraw()
//{
////    if (m_physicsObject != nullptr)
////    {
////		Vector2 pos = getAbsolutePosition();
////		pos = gdata.toScreenPixels(pos.x, pos.y);
////		sf::RectangleShape rec(sf::Vector2f(m_size.x,m_size.y));
////        rec.setPosition(pos.x,pos.y);
////        rec.setOrigin(m_size.x/2,m_size.y/2);
////        rec.setFillColor(sf::Color::Black);
////        rec.setScale(gdata.zoom,gdata.zoom);
////        rec.setRotation(getAbsoluteRotation());
////
////        gdata.window->draw(rec);
////    }
//}
