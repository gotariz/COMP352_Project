#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "general.h"
#include "Particle.h"
#include "physics/PhysicsFactory.h"

class ParticleEmitter
{
    private:
        float accumelator = 0;
    public:
        Vector2 pos;
        Vector2 dir;

        float frequency = 30; // particles per-second
        int duration = 375;
        float speed = 5;
        int size = 1;

        vector<IParticle*>  particles;

    public:
        virtual void createParticle();
        virtual void update();
        virtual void freeResources();
        virtual void drawParticles();
        static bool condition(IParticle* p);
};

#endif // PARTICLEEMITTER_H
