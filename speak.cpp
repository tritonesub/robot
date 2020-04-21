#include "speak.h"
#include <iostream>
#include <speak_lib.h>
using std::cout;
using std::endl;

using std::string;
using std::queue;
using std::shared_ptr;

Speak Speak::instance;

//private constructor (singleton)
Speak::Speak() : 
	synth_flags(espeakCHARS_AUTO | espeakPHONEMES | espeakENDPAUSE),
	queue(), condition() 
{

	const char *voicename = "english";

	espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);

	espeak_SetVoiceByName(voicename);
	espeak_SetParameter(espeakRATE,140,0);
	espeak_SetParameter(espeakCAPITALS,5,0);
	espeak_SetParameter(espeakVOLUME,100,0);
	espeak_SetParameter(espeakRANGE,50,0);
	espeak_SetParameter(espeakPITCH,30,0);
	
	doWork = true;
	t = std::thread(&Speak::worker, this);
}

Speak::~Speak() 
{
	doWork = false;
	condition.notify_all();
	espeak_Terminate();
}

void Speak::say(const shared_ptr<const string>& phrase) 
{
	mutex.lock();
	queue.push(phrase);
	mutex.unlock();
	condition.notify_all();
}

void Speak::worker() 
{
	std::unique_lock<std::mutex> lock(mutex);
	
	while(doWork) {
		condition.wait(lock);
		while(!queue.empty()) {
			espeak_Synth(queue.front()->c_str(), queue.front()->length() + 1, 0, POS_CHARACTER, 0, 
				synth_flags, NULL, NULL);
			espeak_Synchronize();
			queue.pop();
		}
	}
}

void Speak::cleanUp() 
{
	Speak::instance.t.join();
}
