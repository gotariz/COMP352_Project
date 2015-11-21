#include "ExplodeEmitter.h"

ExplodeEmitter::ExplodeEmitter()
{
    //ctor
}

ExplodeEmitter::~ExplodeEmitter()
{
    //dtor
}

//void ExplodeEmitter::createParticle()
//{
//    int num = 10;
//    int counter = 1;
//    int rotation = 0;
//    while (counter <= num)
//    {
//        ExplosionParticle* p = new ExplosionParticle;
//        p->particle_dur = 5000;
//        p->pos = pos;
//        p->img.setTexture(*gdata.assets->getTexture("explosion"));
//        p->img.setRotation(rotation);
//        p->img.setScale(0.1,0.1);
//        p->c = c;
//        p->particle_create();
//
//        particles.push_back(p);
//
//        ++counter;
//        rotation += 360 / num;
//    }
//    enabled = false;
//}

void ExplodeEmitter::createParticle()
{
    int counter = 0;
    while (counter < num_particles)
    {
        float r = utils::getRandom(min_size * 50,max_size * 50);
        r /= 100;

        float x = utils::getRandom(1,2000);
        float y = utils::getRandom(1,2000);
        x -= 1000;
        y -= 1000;

        Vector2 dir(x,y);
        dir.normalise();

        //0.01 - (0.5 - r)
        float d = utils::getRandom(1,(0.5 - r) * 100);
        float velocity = utils::getRandom(10,200);
        velocity /= 100;
        d /= 100;

        dir.setMagnitude(d);

        float dur = 2000 + utils::getRandom(0,2000);

        ExplodeParticle* p = new ExplodeParticle();
        p->setPhysicsObject(gdata.factory->createParticle(pos.x + dir.x,pos.y + dir.y,r,p));
        p->size = r;
        //p->particle_dur = 10000;
        p->particle_create();
        p->c = c;
        dir.setMagnitude(velocity);
        p->setLinearVelocity( dir + (v * 0.25) );
        p->particle_create();
        p->particle_dur = dur;

        particles.push_back(p);

        ++counter;
    }

    enabled = false;
}

void ExplodeEmitter::drawParticles()
{
    //ParticleEmitter::drawParticles();
    for (unsigned i = 0; i < particles.size(); ++i)
    {
        particles.at(i)->particle_draw();
    }
}

