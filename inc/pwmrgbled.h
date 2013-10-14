#ifndef PWMRGBLED_H
#define PWMRGBLED_H

#include "color.h"

class PwmRgbLed {

private:
	PwmRgbLed();

	static const int resolution = 4096;

public:
	PwmRgbLed(shared_ptr<PCA9685> pwm, uint8_t rPin, uint8_t gPin, uint8_t bPin);
	virtual ~FaceLEDAddress();

	shared_ptr<PCA9685> pwm;
	uint8_t redPin;
	uint8_t greenPin;
	uint8_t bluePin;

	void setColor(Color& color);

};

#endif