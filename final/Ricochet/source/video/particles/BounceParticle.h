#ifndef BOUNCEPARTICLE_H
#define BOUNCEPARTICLE_H

#include "general.h"
#include "system/GameData.h"
#include "IParticle.h"


class BounceParticle : public IParticle
{
    public:
        Vector2 pos;

        virtual void particle_draw();
        virtual void particle_create();
        virtual void particle_update();
        virtual void particle_destroy();
};

#endif // BOUNCEPARTICLE_H
