#include "ExplodeParticle.h"

ExplodeParticle::ExplodeParticle()
{
    //ctor
    m_type = PARTICLE;
}

ExplodeParticle::~ExplodeParticle()
{
    //dtor
}

void ExplodeParticle::particle_draw()
{
    onDraw();
}

void ExplodeParticle::particle_create()
{
    circle.setFillColor(c);
    circle.setPointCount(8);
}

void ExplodeParticle::particle_update()
{

}

void ExplodeParticle::particle_destroy()
{
    deletePhysicsObject();
}

void ExplodeParticle::onDraw()
{
    if (m_physicsObject != nullptr)
    {
		Vector2 pos = getAbsolutePosition();
		pos = gdata.toScreenPixels(pos.x, pos.y);

		circle.setRadius(((size * WORLD_SCALE) * gdata.zoom));
		circle.setOrigin(circle.getRadius(),circle.getRadius());
        circle.setPosition(pos.x,pos.y);

        gdata.window->draw(circle);
    }
}

