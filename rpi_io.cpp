#include "rpi_io.h"
#include <bcm2835.h>

//private Rpi_IO constructor (singleton)
Rpi_IO::Rpi_IO() {
	if (!bcm2835_init())
		throw "bcm2835 cannot initialize. You need root access."

	bcm2835_i2c_begin(); //initialize i2c
	bcm2835_spi_begin();//initialize spi

	//initialize pin vars based on raspberry pi version
	//todo: these are currently set for v2.0
	//need to change values if running on v1.0
	PIN_07 = 4;
	PIN_08 = 14;
	PIN_10 = 15;
	PIN_11 = 17;
	PIN_12 = 18;
	PIN_13 = 27;
	PIN_15 = 22;
	PIN_16 = 23;
	PIN_18 = 24;
	PIN_22 = 25;
}

Rpi_IO::~Rpi_IO() {
	
	bcm2835_i2c_end(); //cleanup i2c
	bcm2835_spi_end(); //cleanup spi

	bcm2835_close();
}


//public static methods
void Rpi_IO::i2c_write(uint address, const vector<uint8_t>& writeBuf) {
	Rpi_IO::i2c_mutex.lock();


	Rpi_IO::i2c_mutex.unlock();
}

void Rpi_IO::i2c_read(uint address, const vector<uint8_t>& readBuf, uint size) {
	Rpi_IO::i2c_mutex.lock();

	Rpi_IO::i2c_mutex.unlock();
}

void Rpi_IO::spi_transfer(uint address, const vector<uint8_t>& writeBuf, vector<uint8_t>& readBuf) {
	Rpi_IO::spi_mutex.lock();

	Rpi_IO::spi_mutex.unlock();
}

uint8_t Rpi_IO::read(uint8_t pin) {
	return 0;
}

void Rpi_IO::write(uint8_t pin, uint8_t value) {

}

void Rpi_IO::config_pin(uint8_t pin, uint8_t config) {
	if(config & PULLUP)
		bcm2835_gpio_set_pud(pin, bcm2835PUDControl.BCM2835_GPIO_PUD_UP);
	else if(config & PULLDOWN)
		bcm2835_gpio_set_pud(pin, bcm2835PUDControl.BCM2835_GPIO_PUD_DOWN);
	else
		bcm2835_gpio_set_pud(pin, bcm2835PUDControl.BCM2835_GPIO_PUD_OFF);

	if(config & INPUT)
		bcm2835_gpio_fsel(pin, bcm2835FunctionSelect.BCM2835_GPIO_FSEL_INPT);
	else if(config & OUTPUT)
		bcm2835_gpio_fsel(pin, bcm2835FunctionSelect.BCM2835_GPIO_FSEL_OUTP);
	else 
		throw "Need to configure input or output."

}