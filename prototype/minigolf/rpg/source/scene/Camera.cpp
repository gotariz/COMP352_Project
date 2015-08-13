#include "Camera.h"

int Camera::getScreenX()
{
    return m_x * (WORLD_SCALE * gdata.zoom);
}

int Camera::getScreenY()
{
    return -m_y * (WORLD_SCALE * gdata.zoom);
}
