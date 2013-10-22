#ifndef FACE_H
#define FACE_H

#include "pca9685.h"
#include "pwmrgbled.h"
#include "color.h"
#include <memory>
#include <stdint.h>
#include <vector>

#define MIN_PAN 0
#define MAX_PAN 180
#define MIN_TILT 15
#define MAX_TILT 100
#define TILT_CHANNEL 6
#define PAN_CHANNEL 7 
#define PWM_FREQ 60 


typedef enum {
	RIGHT_EYE = 1,
	LEFT_EYE = 2,
	EYES = 3,
	RIGHT_MOUTH = 4,
	CENTER_RIGHT_MOUTH = 8,
	CENTER_MOUTH = 16,
	CENTER_LEFT_MOUTH = 32,
	LEFT_MOUTH= 64,
	MOUTH = 124
} FaceLED;

typedef enum {
	RED, ORANGE, YELLOW, GREEN, TURQUOISE, LIGHT_BLUE, DARK_BLUE, PURPLE, PINK, WHITE, BLACK		
} PaletteColor; 

class Face {

private:

	std::shared_ptr<PCA9685> pwm1;
	std::shared_ptr<PCA9685> pwm2;
	std::shared_ptr<PCA9685> face_pwm;
	std::shared_ptr<PwmRgbLed> LEDs[7];
	std::vector<Color> palette;

	Face();
	Face(Face const&);
	void operator=(Face const&);
	~Face();

public:
	
	static Face& getInstance() {
		static Face instance;
		return instance;
	}

	void setColor(const Color& color, const uint8_t LEDMask);
	void setColor(PaletteColor color, const uint8_t LEDMask);
	void carousel(unsigned int rev, const std::vector<Color>& colors);
	void carousel(unsigned int rev);

	void tilt(unsigned int deg);
	void pan(unsigned int deg);
};

#endif
