#include color.h

Color::Color() {}

Color::Color(uint8_t R, uint8_t G, uint8_t B) 
{
	Red(R);
	Green(G);
	Blue(B);
}

void Color::Red(uint8_t R) 
{
	_R = R;
}

uint8_t Color::Red() 
{
	return _R;
}

void Color::Green(uint8_t G)
{
	_G = G;
}

uint8_t Color::Green()
{
	return _G;
}

void Color::Blue(uint8_t B)
{
	_B = B;
}

uint8_t Color::Blue()
{
	return _B;
}