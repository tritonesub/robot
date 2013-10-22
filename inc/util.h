#ifndef UTIL_H
#define UTIL_H

inline double map_range(const int value, const int fromMin, const int fromMax, const int toMin, const int toMax)
{
	return (static_cast<float>(value) - fromMin)/(fromMax - fromMin) * (toMax - toMin) + toMin;
}

#endif
