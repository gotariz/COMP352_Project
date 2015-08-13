#ifndef CAMERA_H
#define CAMERA_H

#include "general.h"

#include "system/GameData.h"

class Camera
{
    public:
		Camera(){}
		virtual ~Camera(){}

    public:

        float m_x = 0; // physics positions
        float m_y = 0;
        float m_w = 0; // pixel dimensions
        float m_h = 0;

        int getScreenX();
        int getScreenY();
};

#endif // CAMERA_H
