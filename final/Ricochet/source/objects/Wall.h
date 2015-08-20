#ifndef WALL_H
#define WALL_H

#include "general.h"
#include "Object.h"

class Wall : public Object
{
    public:
        Wall();
        virtual ~Wall();

    public:
        virtual void onUpdate();
        virtual void onDraw();

        Vector2     m_size;

        bool		m_moving = false;
		int			m_nextPoint = 2;
		Vector2		m_point1;
		Vector2		m_point2;
		float		m_time = 0;
		float		m_duration;
};

#endif // WALL_H
