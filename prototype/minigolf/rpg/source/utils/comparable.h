#ifndef COMPARABLE_H
#define COMPARABLE_H

class Comparable
{
	public:
		int heapIndex = 0;
		virtual int getValue() = 0;
		virtual int compare() = 0;
};

#endif //COMPARABLE_H
