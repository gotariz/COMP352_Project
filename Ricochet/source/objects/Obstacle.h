#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "general.h"
#include "gObject.h"


class Obstacle : public gObject
{
    public:
        Obstacle();
        virtual ~Obstacle();

    protected:
        bool        m_enabled = true;
        bool        m_enabledMovement = true;
        bool        m_enabledRotation = true;

        Vector2     m_vel;
        float       m_rotVel = 0;
        int         m_colCat = 0;
        int         m_colMask = 0;

    public:
        virtual void onUpdate();
        //virtual void onDraw();

        int switch_mask = SW_ENB;

        // things to keep track of when disabling movement, rotation and object

        bool getEnabled();
        bool getEnabledMovement();
        bool getEnabledRotation();

        void enable(bool enable);
        void enableMovement(bool enable);
        void enableRotation(bool enable);


        bool		m_moving = false;
		Vector2		m_dest;
		Vector2		m_point1;
		Vector2		m_point2;
		float		m_time = 0;
		float		m_duration;
};

#endif // OBSTACLE_H
