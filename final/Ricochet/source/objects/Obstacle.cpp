#include "Obstacle.h"

Obstacle::Obstacle()
{
    //ctor
}

Obstacle::~Obstacle()
{
    //dtor
}

void Obstacle::onUpdate()
{
	if (m_moving)
	{
		Vector2 delta;
		Vector2 dist_v = m_point1 - m_point2;
		float dist = dist_v.getMagnitude();

		delta = m_point2 - m_point1;
		delta.normalise();
		delta.setMagnitude(dist * (m_time / m_duration));

		if (m_nextPoint == 1) // time is increasing
		{
			m_time += gdata.m_timeDelta;
			if (m_time >= m_duration)
			{
				m_time = m_duration - (m_time - m_duration);
				m_nextPoint = 2;
			}
		}
		else if (m_nextPoint == 2)
		{
			m_time -= gdata.m_timeDelta;
			if (m_time <= 0)
			{
				m_time = 0 - m_time;
				m_nextPoint = 1;
			}
		}

		setAbsolutePosition(m_point1 + delta);
	}
}

void Obstacle::onDraw()
{
    if (m_physicsObject != nullptr)
    {
		Vector2 pos = getAbsolutePosition();
		pos = gdata.toPixels(pos.x, pos.y);
		pos.x -= gdata.camera->getScreenX();
		pos.y -= gdata.camera->getScreenY();

		sf::RectangleShape rec(sf::Vector2f(m_size.x,m_size.y));
        rec.setPosition(pos.x,pos.y);
        rec.setOrigin(m_size.x/2,m_size.y/2);
        rec.setFillColor(sf::Color::Black);
        rec.setScale(gdata.zoom,gdata.zoom);
        rec.setRotation(getAbsoluteRotation());

        gdata.window->draw(rec);
    }
}
