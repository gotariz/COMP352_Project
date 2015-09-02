#ifndef BOUNCEEMITTER_H
#define BOUNCEEMITTER_H

#include "ParticleEmitter.h"
#include "BounceParticle.h"


class BounceEmitter : public ParticleEmitter
{
    public:
        float frequency = 30; // particles per-second
        int duration = 375;

        bool spawn = false;

        virtual void createParticle();
};

#endif // BOUNCEEMITTER_H
