#include "rpi_io.h"
#include <bcm2835.h>
#include <vector>
#include <mutex>
#include <iostream>
using std::cout;
using std::endl;

using std::vector;

std::mutex i2c_mutex;
std::mutex spi_mutex;

Rpi_IO Rpi_IO::instance = Rpi_IO();

//private Rpi_IO constructor (singleton)
Rpi_IO::Rpi_IO() {
	if (!bcm2835_init())
		throw "bcm2835 cannot initialize. You need root access.";

	bcm2835_i2c_begin(); //initialize i2c
	bcm2835_spi_begin();//initialize spi
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
 	cout << "destructor called" << endl;	
//	bcm2835_i2c_end(); //cleanup i2c
//	bcm2835_spi_end(); //cleanup spi

	bcm2835_close();
}


//public static methods
void Rpi_IO::i2c_set_address(uint8_t address)
{
	bcm2835_i2c_setSlaveAddress(address);
}

void Rpi_IO::i2c_write(const uint8_t reg, uint8_t data)
{
	vector<uint8_t> buf(2);
	buf.at(0) = reg;
	buf.at(1) = data;
	i2c_write(buf);
}

void Rpi_IO::i2c_write(const uint8_t reg, std::vector<uint8_t>& writeBuf)
{
	writeBuf.insert(writeBuf.begin(), reg);
	i2c_write(writeBuf);
}

void Rpi_IO::i2c_write(const vector<uint8_t> &writeBuf) {
	i2c_mutex.lock();
	cout << "register: " << std::hex << (unsigned int)writeBuf[0] << endl;
	cout << "data: " << std::hex << (unsigned int)writeBuf[1] << endl;
	cout << "size: " << writeBuf.size() << endl;
	cout << "result: " << bcm2835_i2c_write(reinterpret_cast<const char *>(&writeBuf[0]), writeBuf.size()) << endl;
	i2c_mutex.unlock();
}

void Rpi_IO::i2c_write(const uint8_t value) {
	i2c_mutex.lock();
	bcm2835_i2c_write(reinterpret_cast<const char *>(&value), 1);
	i2c_mutex.unlock();
}

uint8_t Rpi_IO::i2c_readU8(uint8_t address, uint8_t reg) {
	i2c_mutex.lock();
	char data = 0;
	bcm2835_i2c_read_register_rs(reinterpret_cast<char*>(&address), &data, 1);
	i2c_mutex.unlock();
    cout << "read: " << std::hex << (int)data << endl;	
	return data;
}

void Rpi_IO::spi_transfer(uint8_t address, const vector<uint8_t> &writeBuf, vector<uint8_t>& readBuf) {
	spi_mutex.lock();

	spi_mutex.unlock();
}

uint8_t Rpi_IO::read(uint8_t pin) {
	return 0;
}

void Rpi_IO::write(uint8_t pin, uint8_t value) {

}

void Rpi_IO::config_pin(uint8_t pin, uint8_t config) {
	if(config & PULLUP)
		bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);
	else if(config & PULLDOWN)
		bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_DOWN);
	else
		bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_OFF);

	if(config & INPUT)
		bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
	else if(config & OUTPUT)
		bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
	else 
		throw "Need to configure input or output.";

}
