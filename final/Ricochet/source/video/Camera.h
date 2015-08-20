#ifndef CAMERA_H
#define CAMERA_H

#include "general.h"

#include "system/GameData.h"

class Camera
{
    public:
		Camera(float _x = 0, float _y = 0, float _w = 0, float _h = 0)
		{
		    x = _x;
		    y = _y;
		    w = _w;
		    h = _h;
        }

		virtual ~Camera(){}

    public:

        float x = 0; // physics positions
        float y = 0;
        float w = 0; // pixel dimensions
        float h = 0;

        int getScreenX();
        int getScreenY();
};

#endif // CAMERA_H
