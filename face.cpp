#include "face.h"
#include "pwmrgbled.h"
#include "util.h"
#include <math.h>
#include <memory>
#include <thread>

using std::shared_ptr;
using std::vector;


Face::Face() 
{
	pwm1 = shared_ptr<PCA9685>(new PCA9685(0x40));
	pwm1->setFrequency(PWM_FREQ);
	pwm2 = shared_ptr<PCA9685>(new PCA9685(0x41));
	pwm2->setFrequency(PWM_FREQ);

	LEDs[0] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm2, 0, 1, 2)); //right eye
	LEDs[1] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm2, 3, 4, 5)); //left eye
	LEDs[2] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 0, 1, 2)); //right mouth
	LEDs[3] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 3, 4, 5));
	LEDs[4] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 6, 7, 8)); //center mouth
	LEDs[5] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 9, 10, 11));
	LEDs[6] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 12, 13, 14)); //left mouth

	palette = vector<Color>();
	palette.push_back(Color(150,0,0));
	palette.push_back(Color(200,10,0));
	palette.push_back(Color(150,45,0));
	palette.push_back(Color(0,100,0));
	palette.push_back(Color(5,92,110));
	palette.push_back(Color(20,50,130));
	palette.push_back(Color(0,0,120));
	palette.push_back(Color(20,0,60));
	palette.push_back(Color(100,0,20));
	palette.push_back(Color(50,30,50));
	palette.push_back(Color(1,1,1));
}

Face::~Face()
{

}

void Face::setColor(const Color& color, const uint8_t LEDMask) 
{

	for(int i=0; i<7; i++) {
		if((LEDMask >> i) & 0x01) {
			LEDs[i]->setColor(color);	
		}
	}
}

void Face::setColor(PaletteColor color, const uint8_t LEDMask) 
{
	setColor(palette.at(color), LEDMask);
}

void Face::carousel(unsigned int rev, const vector<Color>& colors)
{
	for(unsigned int i=0; i<rev; i++) {
		for(unsigned int j=0; j<colors.size(); j++) {

		}
	}
}

void Face::carousel(unsigned int rev)
{
	carousel(rev, palette);
}

void Face::tilt(unsigned int deg)
{
//	if(deg <= MAX_TILT && deg >= MIN_TILT) {
		pwm2->setPWM(TILT_CHANNEL, 0, floor(deg/((1000000/PWM_FREQ)/4096)));
//		face_pwm->setPWM(TILT_CHANNEL, 0, floor(map_range(deg, MIN_TILT, MAX_TILT, 0, PCA9685::RESOLUTION)));
//	}
}

void Face::pan(unsigned int deg)
{
//	if(deg <= MAX_PAN && deg >= MIN_PAN) {
		pwm2->setPWM(PAN_CHANNEL, 0, floor(deg/((1000000/PWM_FREQ)/4096)));
//		face_pwm->setPWM(PAN_CHANNEL, 0, floor(map_range(deg, MIN_PAN, MAX_PAN, 0, PCA9685::RESOLUTION)));
//	}
}

