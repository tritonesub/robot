#include "pca9685.h"
#include "rpi_io.h"
#include <math.h>
#include <chrono>
#include <thread>
#include <vector>

using std::vector;

PCA9685::PCA9685(uint8_t address) {

	this->address = address;
	Rpi_IO::i2c_write(address, static_cast<uint8_t>(_MODE1), static_cast<uint8_t>(0x00));

}

void PCA9685::setFrequency(int freq) {

	frequency = freq;

	float value = 25000000.0; //25MHz
	value /= 4096.0; //12-bit
	value /= frequency;
	value -= 1.0;

	value = floor(value + 0.5);
	uint8_t oldmode = Rpi_IO::read(address);
	uint8_t newmode = (oldmode & 0x7F) | 0x10;
	
	Rpi_IO::i2c_write(static_cast<uint8_t>(address), static_cast<uint8_t>(_MODE1), newmode);
	Rpi_IO::i2c_write(static_cast<uint8_t>(address), static_cast<uint8_t>(_PRESCALE), static_cast<uint8_t>(floor(value)));
	Rpi_IO::i2c_write(static_cast<uint8_t>(address), static_cast<uint8_t>(_MODE1), newmode);

	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	Rpi_IO::i2c_write(static_cast<uint8_t>(address), static_cast<uint8_t>(_MODE1), oldmode | 0x80);

}

void PCA9685::setPWM(unsigned int channel, unsigned int on, unsigned int off) 
{
    //send vector or array 	
	vector<uint8_t> val(2);
	val.at(0) = _LED0_ON_L + 4 * channel;
	val.at(1) = on & 0xFF;
	Rpi_IO::i2c_write(address, val);

	val.at(0) = _LED0_ON_H + 4 * channel;
	val.at(1) = on >> 8;
	Rpi_IO::i2c_write(address, val);

	val.at(0) = _LED0_OFF_L + 4 * channel;
	val.at(1) = off & 0xFF;
	Rpi_IO::i2c_write(address, val);

	val.at(0) = _LED0_OFF_H + 4 * channel;
	val.at(1) = off >> 8;
	Rpi_IO::i2c_write(address, val);
}
