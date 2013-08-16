#include "speak.h"

using std::string;

//private constructor (singleton)
Speak::Speak() : 
	synth_flags(espeakCHARS_AUTO | espeakPHONEMES | espeakENDPAUSE) {

	const char *voicename = "english";
	espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);

	espeak_SetVoiceByName(voicename);
	espeak_SetParameter(espeakRATE,140,0);
	espeak_SetParameter(espeakCAPITALS,5,0);
	espeak_SetParameter(espeakVOLUME,100,0);
	espeak_SetParameter(espeakRANGE,50,0);
	espeak_SetParameter(espeakPITCH,30,0);

}

Speak::~Speak() {
	espeak_Terminate();
}

void Speak::say(const string& phrase) {
	espeak_Synth(phrase.c_str(), phrase.length() + 1, 0, POS_CHARACTER, 0, 
		synth_flags, NULL, NULL);
	espeak_Synchronize();
}
