#ifndef LASER_H
#define LASER_H

#include "general.h"
#include "Obstacle.h"
#include "ParticleEmitter.h"

class Laser : public Obstacle
{
    public:
        Laser();
        virtual ~Laser();

    public:
        ParticleEmitter emitter;

        float start_angle = 0;
        float delta_angle = 0;
        float r_duration = 0;
        float r_time = 0;
        bool increasing = false;
        bool rotating = false;

        Vector2 rotated_laser;
        Vector2 laser_dir;
		Vector2	laser;
		Vector2 laserPos;

        virtual void onUpdate();
		virtual void onDraw();

		void rotateLaser();
		void moveLaser();
		void raycast();
};

#endif // LASER_H
