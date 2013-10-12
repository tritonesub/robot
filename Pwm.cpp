#include "pwm.h"
#include "rpi_io.h"
#include <chrono>
#include <thread>

Pwm::Pwm(int address = 0x40) {

	this->adress = adresss;
	Rpi_IO::write(address, _MODE1, 0x00);

}

Pwm::setFrequency(float freq) {

	float value = 25000000.0; //25MHz
	value /= 4096.0; //12-bit
	value /= freq;
	value -= 1.0;

	value = floor(value + 0.5);
	uint8_t oldmode = Rpi_IO::read(address);
	uint8_t newmode = (oldmode & 0x7F) | 0x10;
	
	Rpi_IO::write(address, _MODE1, newmode);
	Rpi_IO::write(address, _PRESCALE, static_cast<uint8_t>(floor(value)));
	Rpi_IO::write(address, _MODE1, newmode);

	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	Rpi_IO::write(address, _MODE1, oldmode | 0x80);

}

Pwm::setPWM(uint channel, uint on, uint off) 
{
	Rpi_IO::write(address, _LED0_ON_L + 4 * channel, on & 0xFF);
	Rpi_IO::write(address, _LED0_ON_H + 4 * channel, on >> 8);
	Rpi_IO::write(address, _LED0_OFF_L + 4 * channel, off & 0xFF);
	Rpi_IO::write(address, _LED0_OFF_H + 4 * channel, off >> 8);
}