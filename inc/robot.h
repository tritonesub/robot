#ifndef ROBOT_H
#define ROBOT_H

#include <string>

class Robot {

public:

	//constructors
	Robot();
	~Robot();

	//methods
	int run();

private:
	
	bool halt;

	//methods
	void init();	

	//static
	static int getIP(std::string& ip);
};

#endif //robot.h
