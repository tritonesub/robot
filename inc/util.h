#ifndef UTIL_H
#define UTIL_H

inline double map_range(const int value, const int fromMin, const int fromMax, const int toMin, const int toMax)
{
	return (value - fromMin)/(fromMax - fromMin) * (toMax - toMin) + toMin;
}

#endif
