#ifndef PARTICLE_H
#define PARTICLE_H

#include "general.h"
#include "IParticle.h"
#include "objects/gObject.h"

class Particle : public IParticle, public gObject
{
    public:
        Particle(){
            m_type = PARTICLE;
        }

        Vector2 pos;
        int size = 0;

        sf::Color c = sf::Color::Red;
        virtual void particle_draw();
        virtual void particle_create();
        virtual void particle_update();
        virtual void particle_destroy();
};

#endif // PARTICLE_H
