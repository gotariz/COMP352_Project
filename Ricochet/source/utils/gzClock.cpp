#include "gzClock.h"

gzClock::gzClock()
{
	//old_time = high_resolution_clock::now();
}

float gzClock::getCurrentTimeSeconds()
{
	std::chrono::high_resolution_clock::now();
	return static_cast<float>(clock()) / static_cast<float>(CLOCKS_PER_SEC);
}

unsigned gzClock::getCurrentTimeMilliseconds()
{
	return (static_cast<float>(clock()) / static_cast<float>(CLOCKS_PER_SEC)) * 1000.f;
}

double gzClock::getDeltaSeconds()
{
	high_resolution_clock::time_point current_time = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(current_time - old_time);
	old_time = current_time;
	return time_span.count();
}

long long gzClock::getDeltaMilliseconds()
{
	high_resolution_clock::time_point current_time = high_resolution_clock::now();
	long long delta = duration_cast<std::chrono::milliseconds>(current_time - old_time).count();
	old_time = current_time;
	return delta;
}

long long gzClock::getDeltaMicroseconds()
{
	high_resolution_clock::time_point current_time = high_resolution_clock::now();
	long long delta = duration_cast<std::chrono::microseconds>(current_time - old_time).count();
	old_time = current_time;
	return delta;
}

long long gzClock::getDeltaNanoseconds()
{
	high_resolution_clock::time_point current_time = high_resolution_clock::now();
	long long delta = duration_cast<std::chrono::nanoseconds>(current_time - old_time).count();
	old_time = current_time;
	return delta;
}








