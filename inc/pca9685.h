#ifndef PCA9685_H
#define PCA9685_H



class PCA9685 {
	//registers
private:
	
	const static int _SUBADR1 = 0x02;
	const static int _SUBADR2 = 0x03;
	const static int _SUBADR3 = 0x04;
	const static int _MDOE1 = 0x00;
	const static int _PRESCALE = 0xFE;
	const static int _LED0_ON_L = 0x06;
	const static int _LED0_ON_H = 0x07;
	const static int _LED0_OFF_L = 0x08;
	const static int _LED0_OFF_H = 0x09;
	const static int _ALL_LED_ON_L = 0xFA;
	const static int _ALL_LED_ON_H = 0xFB;
	const static int _ALL_LED_OFF_L = 0xFC;
	const static int _ALL_LED_OFF_H = 0xFD;

	int address;
	int frequency;

	PCA9685();

public:
	const static uint resolution = 4096;
	
	PCA9685(int address = 0x40);


	setFrequency(int freq);
	setPWM(uint channel, uint on, uint off);

};

#endif
