#ifndef UTIL_H
#define UTIL_H

inline double map_range(int value, int fromMin, int fromMax, int toMin, int toMax)
{
	return (value - fromMin)/(fromMax - fromMin) * (toMax - toMin) + toMin;
}

#endif