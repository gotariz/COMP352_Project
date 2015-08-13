#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "gzClock.h"
#include "vector2.h"
#include "glPriorityQueue.h"
#include "gzHeap.h"

class utils {
	public:
		static float toAngle(float rotation);
		static int	getRandom(int min, int max);
};

#endif // UTILS_H_INCLUDED