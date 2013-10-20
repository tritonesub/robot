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

	LEDs[0] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm2, 1, 2, 3)); //right eye
	LEDs[1] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm2, 4, 5, 6)); //left eye
	LEDs[2] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 1, 2, 3)); //right mouth
	LEDs[3] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 4, 5, 6));
	LEDs[4] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 7, 8, 9)); //center mouth
	LEDs[5] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 10, 11, 12));
	LEDs[6] = shared_ptr<PwmRgbLed>(new PwmRgbLed(pwm1, 13, 14, 15)); //left mouth

	palette[PaletteColor::RED] = shared_ptr<Color>(new Color(150,0,0));
	palette[PaletteColor::ORANGE] = shared_ptr<Color>(new Color(200,10,0));
	palette[PaletteColor::YELLOW] = shared_ptr<Color>(new Color(150,45,0));
	palette[PaletteColor::GREEN] = shared_ptr<Color>(new Color(0,100,0));
	palette[PaletteColor::TURQUOISE] = shared_ptr<Color>(new Color(5,92,110));
	palette[PaletteColor::LIGHT_BLUE] = shared_ptr<Color>(new Color(20,50,130));
	palette[PaletteColor::DARK_BLUE] = shared_ptr<Color>(new Color(0,0,120));
	palette[PaletteColor::PURPLE] = shared_ptr<Color>(new Color(20,0,60));
	palette[PaletteColor::PINK] = shared_ptr<Color>(new Color(100,0,20));
	palette[PaletteColor::WHITE] = shared_ptr<Color>(new Color(50,30,50));
	palette[PaletteColor::BLACK] = shared_ptr<Color>(new Color(0,0,0));

}

Face::~Face()
{

}

void Face::setColor(const Color& color, const uint8_t LEDMask) 
{

	for(int i; i<7; i++) {
		if((LEDMask >> i) & 0x01) {
			LEDs[i]->setColor(color);	
		}
	}
}

void Face::setColor(PaletteColor color, const uint8_t LEDMask) 
{
	setColor(*(palette.at(color)), LEDMask);
}

void Face::carousel(unsigned int rev, const vector<shared_ptr<Color>>& colors)
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

void Face::pan_tilt(unsigned int pan, unsigned int tilt)
{
	this->pan(pan);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	this->tilt(tilt);
}
