#ifndef SPARKSEMITTER_H
#define SPARKSEMITTER_H

#include "general.h"
#include "ParticleEmitter.h"


class SparksEmitter : public ParticleEmitter
{
    public:
        float frequency = 0; // particles per-second
        int duration = 0;
        float speed = 0;
        int size = 0;

        virtual void createParticle();
};

#endif // SPARKSEMITTER_H
