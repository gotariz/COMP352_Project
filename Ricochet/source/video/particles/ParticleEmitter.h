#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "general.h"
#include "IParticle.h"
#include "physics/PhysicsFactory.h"

class ParticleEmitter
{
    protected:
        float accumelator = 0;
    public:
        Vector2 pos;
        Vector2 dir;
        bool enabled = false;

        vector<IParticle*>  particles;

    public:
        virtual void createParticle() = 0;
        virtual void update();
        virtual void freeResources();
        virtual void drawParticles();
        static bool condition(IParticle* p);
};

#endif // PARTICLEEMITTER_H
