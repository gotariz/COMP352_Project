#include "Hole.h"

Hole::Hole()
{
    //ctor
    m_type = HOLE;
}

Hole::~Hole()
{
    //dtor
}

void Hole::onUpdate()
{
    m_image.setOrigin( m_image.getTexture()->getSize().x / 2, m_image.getTexture()->getSize().y / 2 );
}

void Hole::onEnterCollision(CollisionData cd)
{
    if (cd.objectB->m_type == PLAYER)
    {
        if (gdata.countdown <= 0)
        {
            cout << "you won" << endl;
            m_image.setTexture(*gdata.assets->getTexture("hole_on"));
            gdata.level += 1;
            gdata.countdown = 1.f;
            cd.objectB->setLinearVelocity(Vector2(0,0));
        }
        //gdata.delay_reload = true;
    }
}


