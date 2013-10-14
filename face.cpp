#include "face.h"
#include "pwmrgbled.h"
#include "util.h"

Face::Face() 
{
	pwm1(new PCA9685(0x40));
	pwm2(new PCA9685(0x41));
	face_pwm(pwm2);

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

	for(int i; i<7; i++) {
		if((LEDMask >> i) & 0x01) {
			LEDs[i]->setColor(color);	
		}
	}
}

Face::tilt(uint deg)
{
	if(deg <= MAX_TILT && deg >= MIN_TILT) {
		face_pwm->setPWM(TILT_CHANNEL, floor(map_range(deg, MIN_TILT, MAX_TILT, 0, PCA9685::RESOLUTION)))
	}
}

Face::pan(uint deg)
{
	if(deg <= MAX_PAN && deg >= MIN_PAN) {
		face_pwm->setPWM(PAN_CHANNEL, floor(map_range(deg, MIN_PAN, MAX_PAN, 0, PCA9685::RESOLUTION)))
	}
}