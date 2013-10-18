#include "rpi_io.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <vector>
#include <mutex>

using std::vector;

std::mutex i2c_mutex;
std::mutex spi_mutex;

int Rpi_IO::fd = 0;

Rpi_IO Rpi_IO::instance = Rpi_IO();

//private Rpi_IO constructor (singleton)
Rpi_IO::Rpi_IO() {
	wiringPiSetup();

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

Rpi_IO::~Rpi_IO() {
}


//public static methods
void Rpi_IO::i2c_set_address(uint8_t address)
{
    fd = wiringPiI2CSetup(address);
}

void Rpi_IO::i2c_write(const uint8_t reg, uint8_t data)
{
	wiringPiI2CWriteReg8(fd, reg, data);
}

void Rpi_IO::i2c_write(const uint8_t reg, std::vector<uint8_t>& writeBuf)
{
}

void Rpi_IO::i2c_write(const vector<uint8_t> &writeBuf) {
}

void Rpi_IO::i2c_write(const uint8_t value) {
}

uint8_t Rpi_IO::i2c_readU8(uint8_t reg) {
	int data = wiringPiI2CReadReg8(fd, reg);
	return data;
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
