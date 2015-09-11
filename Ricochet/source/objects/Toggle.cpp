#include "Toggle.h"

Toggle::Toggle()
{
    //ctor
    m_type = TOGGLE;
}

Toggle::~Toggle()
{
    //dtor
}

void Toggle::onCreate()
{

}

void Toggle::onDestroy()
{

}

void Toggle::onUpdate()
{
    if (switch_type == TIMED)
    {
        if (active)
        {
            time += gdata.m_timeDelta;
            cout << time << endl;
            if (time >= max_time)
            {
                m_image.setTexture(*off);
                // deactivate
                time = 0;
                active = false;
            }
        }
    }

}

void Toggle::onCollision(Object* objectB)
{
    if (!objectB) return;

    if (switch_type == TIMED && !active)
    {
        m_image.setTexture(*on);
        active = true;
    }
}

void Toggle::onEnterCollision(CollisionData cd)
{
    if (!cd.objectB) return;

    if (switch_type == TOGGLE)
    {
        if (active)
        {
            m_image.setTexture(*off);
            // deactivate
        } else {
            m_image.setTexture(*on);
            // activate
        }
        active = !active;
    }
    else if (switch_type == SINGLE || switch_type == CONTINUOUS)
    {
        if (!active)
        {
            active = true;
            m_image.setTexture(*on);
            // activate if not already active
        }
    }
    else if (switch_type == TIMED)
    {
        if (!active)
        {
            active = true;
            m_image.setTexture(*on);
            // activate if not already active
        }
    }
}

void Toggle::onExitCollision(CollisionData cd)
{
    if (!cd.objectB) return;

    if (switch_type == CONTINUOUS)
    {
        active = false;
        m_image.setTexture(*off);
        // deactivate
    }
}

