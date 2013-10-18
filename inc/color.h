#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

class Color {

private:

public:
	Color();
	Color(uint8_t R, uint8_t G, uint8_t B);

	static const unsigned int MAX_RGB = 255;

	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;

};

#endif
