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

void Toggle::toggleObstacles()
{
    gdata.audio->playSound("click");
    // loop through obstacles and enable/disable accordingly
    for (int i = 0; i < obs.size(); ++i)
    {
        Obstacle& o = *obs.at(i);
        if (o.switch_mask & SW_ENB)
        {
            o.enable(!o.getEnabled());
            o.enableRotation(!o.getEnabledRotation());
            o.enableMovement(!o.getEnabledMovement());
        }
        else
        {
            if (o.switch_mask & SW_ROT)     o.enableRotation(!o.getEnabledRotation());
            if (o.switch_mask & SW_MOV)     o.enableMovement(!o.getEnabledMovement());
        }
    }
}


void Toggle::onUpdate()
{
    if (switch_type == TIMED)
    {
        if (active)
        {
            time += gdata.m_timeDelta;
            if (time >= max_time)
            {
                m_image.setTexture(*off);
                toggleObstacles();
                time = 0;
                active = false;
            }
        }
    }

}

void Toggle::onCollision(Object* objectB)
{
    if (!objectB) return;
}

void Toggle::onEnterCollision(CollisionData cd)
{
    if (!cd.objectB) return;

    if (switch_type == TOGGLE)
    {
        if (active)
        {
            m_image.setTexture(*off);
            toggleObstacles();
        } else {
            m_image.setTexture(*on);
            toggleObstacles();
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
            toggleObstacles();
        }
    }
    else if (switch_type == TIMED)
    {
        if (!active)
        {
            active = true;
            m_image.setTexture(*on);
            // activate if not already active
            toggleObstacles();
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
        toggleObstacles();
    }
}

