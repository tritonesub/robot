#ifndef SPEAK_H
#define SPEAK_H

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "speak_lib.h"

class Speak {

private:
	//constructors
	Speak();
	Speak(Speak const&);
	~Speak();
	void operator=(Speak const&);

 	int synth_flags; 
	std::queue<std::shared_ptr<const std::string>> queue;

	std::mutex mutex;
	std::condition_variable condition;
	std::thread t;

	void worker();
	bool doWork;

	static Speak instance;

public:
	void say(const std::shared_ptr<const std::string>& phrase);

	static Speak& getInstance() {
		return instance;
	}

	static void cleanUp();
};

#endif
