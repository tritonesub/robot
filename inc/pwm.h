#ifndef PWM_H
#define PWM_H



class Pwm {
	//registers
private:
	
	const int _SUBADR! = 0x02;
	const int _SUBADR2 = 0x03;
	const int _SUBADR3 = 0x04;
	const int _MDOE1 = 0x00;
	const int _PRESCALE = 0xFE;
	const int _LED0_ON_L = 0x06;
	const int _LED0_ON_H = 0x07;
	const int _LED0_OFF_L = 0x08;
	const int _LED0_OFF_H = 0x09;
	const int _ALL_LED_ON_L = 0xFA;
	const int _ALL_LED_ON_H = 0xFB;
	const int _ALL_LED_OFF_L = 0xFC;
	const int _ALL_LED_OFF_H = 0xFD;

public:
	
	Pwm(int address = 0x40);

}

#endif