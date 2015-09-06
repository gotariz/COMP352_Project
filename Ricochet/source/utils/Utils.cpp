#include "Utils.h"

float utils::toAngle(float rotation)
{
	int intAngle = rotation;
	float safe_angle = rotation - intAngle;
	safe_angle += intAngle % 360;

	if (safe_angle < 0) safe_angle += 360;

	return safe_angle;
}

int utils::getRandom(int min, int max)
{
	return (rand() % max) + min;
}

int utils::roundUp(float num, int clip)
{
    int inum = num;
    float decimal = num - inum;
    int remainder = inum % clip;

    if ( (decimal + remainder) > 0.f)
    {
        inum = inum + (clip - remainder);
    }

    return inum;
}

int utils::roundDown(float num, int clip)
{
    int inum = num;
    int remainder = inum % clip;

    return inum - remainder;
}

int utils::roundNearest(float num, int clip)
{
    int inum = num;
    float remainder = inum % clip;
    remainder += num - inum;

    if (remainder >= (static_cast<float>(clip) / 2.f))
        return roundUp(num,clip);
    else
        return roundDown(num,clip);
}
