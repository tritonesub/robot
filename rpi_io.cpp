#include "rpi_io.h"
#include <bcm2835.h>

using std::vector;

//private Rpi_IO constructor (singleton)
Rpi_IO::Rpi_IO() {
	if (!bcm2835_init())
		throw "bcm2835 cannot initialize. You need root access."

	bcm2835_i2c_begin(); //initialize i2c
	bcm2835_spi_begin();//initialize spi

}

Rpi_IO::~Rpi_IO() {
	
	bcm2835_i2c_end(); //cleanup i2c
	bcm2835_spi_end(); //cleanup spi

	bcm2835_close();
}

void Rpi_IO::i2c_write(uint address, const vector<uint8_t>& writeBuf) {


}

void Rpi_IO::i2c_read(uint address, const vector<uint8_t>& readBuf, uint size) {


}

void Rpi_IO::spi_transfer(uint address, const vector<uint8_t>& writeBuf, vector<uint8_t>& readBuf) {


}

uint8_t read(uint8_t pin) {
	return 0;
}

void write(uint8_t pin, uint8_t value) {

}