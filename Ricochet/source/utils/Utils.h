#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"

#include "gz.h"
#include "Vector2.h"
#include "gzClock.h"

class utils
{
    public:
        static float toAngle(float rotation);
		static int	getRandom(int min, int max);

		static int roundUp(float num, int clip);
		static int roundDown(float num, int clip);
		static int roundNearest(float num, int clip);

		static bool fexists(const std::string& filename);
		static bool fexists(const char *filename);

		static bool isTouching(Vector2 point, sf::RectangleShape box);
		static bool isTouching(Vector2 point, int x, int y, int w, int h);
};

#endif // UTILS_H

