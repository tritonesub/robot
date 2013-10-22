#include "pwmrgbled.h"
#include "color.h"
#include "util.h"
#include <math.h>
#include <memory>

using std::shared_ptr;

PwmRgbLed::PwmRgbLed(const shared_ptr<PCA9685>& pwm, uint8_t rChannel, uint8_t gChannel, uint8_t bChannel)
{
	this->pwm = pwm;
	redChannel = rChannel;
	greenChannel = gChannel;
	blueChannel = bChannel;
	frequency = 60;
}

PwmRgbLed::~PwmRgbLed() {}

void PwmRgbLed::setColor(const Color& color) 
{
	pwm->setPWM(redChannel, 0, PCA9685::RESOLUTION - ceil(map_range(color.Red, 0, Color::MAX_RGB, 0, PCA9685::RESOLUTION)));
	pwm->setPWM(greenChannel, 0, PCA9685::RESOLUTION - ceil(map_range(color.Green, 0, Color::MAX_RGB, 0, PCA9685::RESOLUTION)));
	pwm->setPWM(blueChannel, 0, PCA9685::RESOLUTION - ceil(map_range(color.Blue, 0, Color::MAX_RGB, 0, PCA9685::RESOLUTION)));
}

