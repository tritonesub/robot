#ifndef RPI_IO_H
#define RPI_IO_H
#include <vector>
#include <mutex>

typedef enum {
	PULLUP = 0x01,
	PULLDOWN = 0x03,

} RpiPin;

class Rpi_IO {

private:
	//constructors
	Rpi_IO();
	Rpi_IO(Rpi_IO const&);
	~Rpi_IO();
	
	void operator=(Rpi_IO const&);
	
	static Rpi_IO instance;

	static int fd;

public:
	//only reference
	static const uint8_t PIN_07;
	static const uint8_t PIN_08;
	static const uint8_t PIN_10;
	static const uint8_t PIN_11;
	static const uint8_t PIN_12;
	static const uint8_t PIN_13;
	static const uint8_t PIN_15;
	static const uint8_t PIN_16;
	static const uint8_t PIN_18;
	static const uint8_t PIN_22;

	static const uint8_t PULLUP = 0x01;
	static const uint8_t PULLDOWN = 0x02;
	static const uint8_t INPUT = 0x04;
	static const uint8_t OUTPUT = 0x08;

	static void i2c_set_address(uint8_t address);

	static void i2c_write(const uint8_t reg, const uint8_t data);
	static void i2c_write(const uint8_t reg, std::vector<uint8_t>& writeBuf);
	static void i2c_write(const std::vector<uint8_t>& writeBuf);
	static void i2c_write(const uint8_t value);

	static void i2c_read(std::vector<uint8_t>& readBuf, uint size);
	static uint8_t i2c_readU8(uint8_t reg);

	static void spi_transfer(uint8_t  address, const std::vector<uint8_t>& writeBuf, std::vector<uint8_t>& readBuf);

	static uint8_t read(uint8_t pin);

	static void write(uint8_t pin, const uint8_t value);

	static void config_pin(uint8_t pin, uint8_t config);
};

#endif
