#include "pwmrgbled.h"
#include "color.h"
#include "util.h"
#include <math.h>

PwmRgbLed::PwmRgbLed(shared_ptr<PCA9685> pwm, uint8_t rChannel, uint8_t gChannel, uint8_t bChannel)
{
	this->pwm(pwm);
	redChannel = rChannel;
	greenChannel = gChannel;
	blueChannel = bChannel;
	frequency = 60;
}

PwmRgbLed::~PwmRgbLed() {}

PwmRgbLed::setColor(Color& color) 
{
	pwm->setPWM(redChannel, 0, floor(map_range(color.Red(), 0, MAX_RGB, 0, PCA9685::RESOLUTION));
	pwm->setPWM(greenChannel, 0, floor(map_range(color.Green(), 0, MAX_RGB, 0, PCA9685::RESOLUTION)));
	pwm->setPWM(blueChannel, 0, floor(map_range(color.Blue(), 0, MAX_RGB, 0, PCA9685::RESOLUTION)));
}

