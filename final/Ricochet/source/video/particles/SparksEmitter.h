#ifndef SPARKSEMITTER_H
#define SPARKSEMITTER_H

#include "general.h"
#include "ParticleEmitter.h"


class SparksEmitter : public ParticleEmitter
{
    public:
        float frequency = 30; // particles per-second
        int duration = 375;
        float speed = 5;
        int size = 1;

        virtual void createParticle();
};

#endif // SPARKSEMITTER_H
