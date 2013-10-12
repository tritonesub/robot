#include color.h

Color::Color() {}

Color::Color(uint R, uint G, uint B) 
{
	Red(R);
	Green(G);
	Blue(B);
}

void Color::Red(uint R) 
{
	if(R <= 255)
		_R = R;
	else 
		throw "Invalid parameter value R must be < 255";
}

uint Color::Red() 
{
	return _R;
}

void Color::Green(uint G)
{
	if(G <= 255)
		_G = G;
	else 
		throw "Invalid parameter value G must be < 255";
}

uint Color::Green()
{
	return _G;
}

void Color::Blue(uint B)
{
	if(B <= 255)
		_B = B;
	else
		throw "Invalid parameter value. B must be < 255";
}

uint Color::Blue()
{
	return _B;
}