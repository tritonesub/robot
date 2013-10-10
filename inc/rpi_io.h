#ifndef RPI_IO_H
#define RPI_IO_H
#include <vector>

class Rpi_IO {

private:
	//constructors
	Rpi_IO();
	Rpi_IO(Rpi_IO const&);
	~Rpi_IO();
	void operator=(Rpi_IO const&)

public:
	static Rpi_IO & getInstance() {
		static Rpi_IO instance;
		return instance;
	}

	void i2c_write(int address, const std::vector<uint8_t> writeBuf);
	void i2c_read(int address, std::vector<uint*_t> readBuf, uint size);

	void spi_transfer(int address, const std::vector<uint8_t> writeBuf, std::vector<uint8_t> readBuf);

	uint8_t read(uint8_t pin);
	uint8_t write(uint8_t pin, uint8_t value);
};

#endif