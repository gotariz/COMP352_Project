#include "Utils.h"

bool utils::isTouching(Vector2 point, sf::RectangleShape box)
{
    if (point.x < box.getPosition().x) return false;
    if (point.y < box.getPosition().y) return false;

    if (point.x > box.getPosition().x + box.getSize().x - 1) return false;
    if (point.y > box.getPosition().y + box.getSize().y - 1) return false;

    return true;
}

bool utils::isTouching(Vector2 point, int x, int y, int w, int h)
{
    if (point.x < x) return false;
    if (point.y < y) return false;

    if (point.x > x + w - 1) return false;
    if (point.y > y + h - 1) return false;

    return true;
}


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

bool utils::fexists(const std::string& filename) {
  ifstream ifile(filename.c_str());
  return ifile;
}

bool utils::fexists(const char *filename) {
  ifstream ifile(filename);
  return ifile;
}
