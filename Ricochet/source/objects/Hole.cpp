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

}

void Hole::onDraw()
{
    if (!m_image.getTexture()) return;

    Vector2 pos = gdata.toScreenPixels(getAbsolutePosition());

    m_image.setPosition(pos.x,pos.y);
    m_image.setScale(gdata.zoom,gdata.zoom);
    m_image.setOrigin( m_image.getTexture()->getSize().x / 2, m_image.getTexture()->getSize().y / 2 );
    gdata.window->draw(m_image);

}

void Hole::onEnterCollision(CollisionData cd)
{
    if (cd.objectB->m_type == PLAYER)
    {
        cout << "you won" << endl;
        m_image.setTexture(*gdata.assets->getTexture("hole_on"));
        gdata.reload = true;
        gdata.level += 1;
        if (gdata.level > 9) gdata.level = 9;
        gdata.delay_reload = true;
    }
}


