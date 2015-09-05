#pragma once

#include <time.h>
#include <chrono>


using namespace std::chrono;
class gzClock
{
	public:
		gzClock();
		virtual ~gzClock(){}

		float		getCurrentTimeSeconds();
		unsigned	getCurrentTimeMilliseconds();
		
		double		getDeltaSeconds();
		long long	getDeltaMilliseconds();
		long long	getDeltaMicroseconds();
		long long	getDeltaNanoseconds();

	protected:
		high_resolution_clock::time_point old_time;
		//clock_t old_time;
};

