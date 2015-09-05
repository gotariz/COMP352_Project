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
};

#endif // UTILS_H

