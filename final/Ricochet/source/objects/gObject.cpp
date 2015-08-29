#include "gObject.h"

gObject::gObject()
{
    //ctor
}

gObject::~gObject()
{
    //dtor
}

void gObject::onCreate()
{

}

void gObject::onDestroy()
{

}

void gObject::onUpdate()
{

}

void gObject::onPrePhysicsUpdate()
{

}

void gObject::onPostPhysicsUpdate()
{

}

void gObject::onCollision(Object* objectB)
{

}

void gObject::onEnterCollision(CollisionData cd)
{

}

void gObject::onExitCollision(CollisionData cd)
{

}

void gObject::onDraw()
{
    if (m_image.getTexture() != nullptr)
    {
		Vector2 pos = getAbsolutePosition();
		pos = gdata.toScreenPixels(pos.x, pos.y);
		m_image.setScale(gdata.zoom,gdata.zoom);
		m_image.setRotation(getAbsoluteRotation());
        gdata.window->draw(m_image);
    }
}

