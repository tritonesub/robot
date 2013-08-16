#ifndef SPEAK_H
#define SPEAK_H

#include "speak_lib.h"
#include <string>

class Speak {

private:
	//constructors
	Speak();
	Speak(Speak const&);
	~Speak();
	void operator=(Speak const&);

 	int synth_flags; 

public:
	void say(const std::string& phrase);

	static Speak& getInstance() {
		static Speak instance;
		return instance;
	}
};

#endif
