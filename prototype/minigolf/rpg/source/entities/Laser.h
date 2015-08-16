#pragma once

#include "general.h"
#include "Object.h"

class Laser : public Object
{
	public:
		Laser() {}
		~Laser() {}

		Vector2 laser_dir;
		Vector2	laser;
		Vector2 laserPos;

		float start_angle = 0;
		float delta_angle = 0;
		float r_duration = 0;
		float r_time = 0;
		bool m_rotating = false;
		bool increasing = true;
		Vector2 rotated_laser;

		virtual void onUpdate();
		//virtual void onPrePhysicsUpdate();
		//virtual void onPostPhysicsUpdate();
		//virtual void onCollision(Object* objectB);
		//virtual void onEnterCollision(Object* objectB);
		virtual void onDraw();
};

