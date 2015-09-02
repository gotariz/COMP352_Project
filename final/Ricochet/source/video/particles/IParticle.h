#ifndef IPARTICLE_H_INCLUDED
#define IPARTICLE_H_INCLUDED

class IParticle
{
    public:
        int particle_age = 0;
        int particle_dur = 0;

        virtual void particle_draw() = 0;
        virtual void particle_create() = 0;
        virtual void particle_update() = 0;
        virtual void particle_destroy() = 0;

};

#endif // IPARTICLE_H_INCLUDED
