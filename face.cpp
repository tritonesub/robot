#include "face.h"
#include "pwmrgbled.h"

Face::Face() 
{
	pwm1(new PCA9685(0x40));
	pwm2(new PCA9685(0x41));

	LEDs[0](new PwmRgbLed(pwm2, 1, 2, 3)) //right eye
	LEDs[1](new PwmRgbLed(pwm2) 4, 5, 6)) //left eye
	LEDs[2](new PwmRgbLed(pwm1) 1, 2, 3)) //right mouth
	LEDs[3](new PwmRgbLed(pwm1) 4, 5, 6))
	LEDs[4](new PwmRgbLed(pwm1) 7, 8, 9)) //center mouth
	LEDs[5](new PwmRgbLed(pwm1) 10, 11, 12))
	LEDs[6](new PwmRgbLed(pwm1) 13, 14, 15)) //left mouth

}

Face::~Face()
{

}

Face::setColor(const Color& color, const uint8_t LEDMask) 
{

	
}