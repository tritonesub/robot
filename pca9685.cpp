#include "pca9685.h"
#include "rpi_io.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;


PCA9685::PCA9685(uint8_t address) {

	this->address = address;
	Rpi_IO::i2c_set_address(address);
	Rpi_IO::i2c_write(static_cast<uint8_t>(_MODE1), static_cast<uint8_t>(0x00));

}

void PCA9685::setFrequency(int freq) {

	Rpi_IO::i2c_set_address(address);

	frequency = freq;

	float value = 25000000.0; //25MHz
	value /= 4096.0; //12-bit
	value /= frequency;
	value -= 1.0;

	value = floor(value + 0.5);
	uint8_t oldmode = Rpi_IO::i2c_readU8(_MODE1);
	uint8_t newmode = (oldmode & 0x7F) | 0x10;

	Rpi_IO::i2c_write(static_cast<uint8_t>(_MODE1), newmode);
	Rpi_IO::i2c_write(static_cast<uint8_t>(_PRESCALE), static_cast<uint8_t>(floor(value)));
	Rpi_IO::i2c_write(static_cast<uint8_t>(_MODE1), oldmode);

	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	Rpi_IO::i2c_write(static_cast<uint8_t>(_MODE1), oldmode | 0x80);

}

void PCA9685::setPWM(unsigned int channel, unsigned int on, unsigned int off) 
{
	cout << "set pwm for: " << std::hex << address << endl;
	Rpi_IO::i2c_set_address(address);
	
	Rpi_IO::i2c_write(_LED0_ON_L + 4 * channel, on & 0xFF);
	Rpi_IO::i2c_write(_LED0_ON_H + 4 * channel, on >> 8);

	Rpi_IO::i2c_write(_LED0_OFF_L + 4 * channel, off & 0xFF);
	Rpi_IO::i2c_write(_LED0_OFF_H + 4 * channel, off >> 8);
}
