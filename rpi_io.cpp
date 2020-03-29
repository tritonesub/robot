#include "rpi_io.h"
#include <fcntl.h>
#include <sys/ioctl.h>
//#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <algorithm>
#include <vector>
#include <mutex>
#include <unistd.h>
#include "i2c-dev.h"

using std::vector;

std::mutex i2c_mutex;
std::mutex spi_mutex;

int Rpi_IO::fd = 0;

Rpi_IO Rpi_IO::instance = Rpi_IO();

//private Rpi_IO constructor (singleton)
Rpi_IO::Rpi_IO() {
	
	//need to check for actual board version for re-usability
	//hard code to version 2
	fd = open("/dev/i2c-1", O_RDWR);

	//initialize pin vars based on raspberry pi version
	//todo: these are currently set for v2.0
	//need to change values if running on v1.0
	const uint8_t PIN_07 = 4;
	const uint8_t PIN_08 = 14;
	const uint8_t PIN_10 = 15;
	const uint8_t PIN_11 = 17;
	const uint8_t PIN_12 = 18;
	const uint8_t PIN_13 = 27;
	const uint8_t PIN_15 = 22;
	const uint8_t PIN_16 = 23;
	const uint8_t PIN_18 = 24;
	const uint8_t PIN_22 = 25;
}

Rpi_IO::~Rpi_IO() 
{
	close(fd);
}


//public static methods

int Rpi_IO::i2c_write(const int address, const int reg, int data)
{
	std::lock_guard<std::mutex> lock(i2c_mutex);

	if(ioctl(fd, I2C_SLAVE, address) < 0)
		return -1;

	return i2c_smbus_write_byte_data(fd, reg, address);
}

int Rpi_IO::i2c_write(const int address, vector<std::pair<int,int>> data)
{
	std::lock_guard<std::mutex> lock(i2c_mutex);
	
	if(ioctl(fd, I2C_SLAVE, address) < 0)
		return -1;

	for_each(data.begin(), data.end(), [](std::pair<int,int> val) {
		i2c_smbus_write_byte_data(fd, std::get<0>(val), std::get<1>(val));
	});

	return 0; 
}

int Rpi_IO::i2c_io_callback(const int address, std::function<int (int)> callback)
{
	std::lock_guard<std::mutex> lock(i2c_mutex);

	if(ioctl(fd, I2C_SLAVE, address) < 0)
		return -1;

 	return callback(fd);
}


int Rpi_IO::i2c_read8(const int address, const int reg) {
	std::lock_guard<std::mutex> lock(i2c_mutex);

	if(ioctl(fd, I2C_SLAVE, address) < 0)
		return -1;
	return i2c_smbus_read_byte_data(fd, reg);
}

void Rpi_IO::spi_transfer(uint8_t address, const vector<uint8_t> &writeBuf, vector<uint8_t>& readBuf) {
}

uint8_t Rpi_IO::read(uint8_t pin) {
	return 0;
}

void Rpi_IO::write(uint8_t pin, uint8_t value) {

}

void Rpi_IO::config_pin(uint8_t pin, uint8_t config) {
/*	if(config & PULLUP)
	else if(config & PULLDOWN)
	else

	if(config & INPUT)
	else if(config & OUTPUT)
	else 
		throw "Need to configure input or output.";
*/
}
