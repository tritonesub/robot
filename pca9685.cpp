#include "pca9685.h"
#include "rpi_io.h"
#include <math.h>
#include <linux/i2c-dev.h>
#include <chrono>
#include <thread>
#include <vector>

using std::vector;
using std::pair;

PCA9685::PCA9685(uint8_t address) {

	this->address = address;
	Rpi_IO::i2c_write(address, _MODE1, 0x00);
}

void PCA9685::setFrequency(int freq) {

	frequency = freq;

	float value = 25000000.0; //25MHz
	value /= 4096.0; //12-bit
	value /= frequency;
	value -= 1.0;

	value = floor(value + 0.5);

	Rpi_IO::i2c_io_callback(address, [&](int fd) {
				
		int oldmode = i2c_smbus_read_byte_data(fd, _MODE1);
		int newmode = (oldmode & 0x7F) | 0x10;
		i2c_smbus_write_byte_data(fd, _MODE1, newmode);
		i2c_smbus_write_byte_data(fd, _PRESCALE, floor(value));

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	 
	 	i2c_smbus_write_byte_data(fd, _MODE1, oldmode | 0x80);
		return 0;
	});
}

void PCA9685::setPWM(unsigned int channel, unsigned int on, unsigned int off) 
{
	vector<pair<int,int>> data(4);
	data.push_back(pair<int,int>(_LED0_ON_L + 4 * channel, on & 0xFF));
	data.push_back(pair<int,int>(_LED0_ON_H + 4 * channel, on >> 8));
	data.push_back(pair<int,int>(_LED0_OFF_L + 4 * channel, off & 0xFF));
	data.push_back(pair<int,int>(_LED0_OFF_H + 4 * channel, off >> 8));

	Rpi_IO::i2c_write(address, data);
}
