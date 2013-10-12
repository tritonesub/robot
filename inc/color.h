#ifndef COLOR_H
#define COLOR_H

class Color {

private:
	uint _R;
	uint _G;
	uint _B;

public:
	Color();
	Color(uint R, uint G, uint B);
	virtual ~Color();	

	uint Red();
	void Red(uint R);
	uint Green();
	void Green(uint G);
	uint Blue();
	void Blue(uint B);

};

#endif