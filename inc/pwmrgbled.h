#ifndef PWMRGBLED_H
#define PWMRGBLED_H

#include "color.h"
#include "pca9685.h"
#include <memory>
#include <stdint.h>

class PwmRgbLed {

private:
	PwmRgbLed();

	static const int resolution = 4096;

public:
	PwmRgbLed(const std::shared_ptr<PCA9685>& pwm, uint8_t rPin, uint8_t gPin, uint8_t bPin);
	virtual ~PwmRgbLed();

	std::shared_ptr<PCA9685> pwm;
	uint8_t redChannel;
	uint8_t greenChannel;
	uint8_t blueChannel;

	unsigned int frequency;

	void setColor(const Color& color);

};

#endif
