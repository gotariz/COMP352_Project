#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "general.h"
#include "gObject.h"


class Obstacle : public gObject
{
    public:
        Obstacle();
        virtual ~Obstacle();

    public:
        virtual void onUpdate();
        virtual void onDraw();

        //Vector2     m_size;

        bool		m_moving = false;
		Vector2		m_dest;
		Vector2		m_point1;
		Vector2		m_point2;
		float		m_time = 0;
		float		m_duration;
};

#endif // OBSTACLE_H
