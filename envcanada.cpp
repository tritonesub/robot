#include <sstream>
#include <curl/curl.h>
#include "envcanada.h"

using std::string;
using std::stringstream;

//constants
const string EnvCanada::URL = "http://weather.gc.ca/rss/city/";

//constructors

EnvCanada::EnvCanada(const string& location) : _location(location) {
	load();
}

EnvCanada::~EnvCanada() {}

std::shared_ptr<const Weather> EnvCanada::operator[] (const int i) {
	
	if(i > 4 || forecast.size() < 1)
		return NULL;

	return forecast[i];
}

//public

const std::string& EnvCanada::location() 
{
	return const_cast<string &>(_location);
}

void EnvCanada::location(const string& l) 
{
	_location = l;
	load();
}

void EnvCanada::load() 
{
	
	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();

	stringstream ss;
	
	if(curl) {
		ss << URL << _location << ".xml";
		curl_easy_setopt(curl, CURLOPT_URL, ss.str().c_str());
    	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    	res = curl_easy_perform(curl);

    	if(res != CURLE_OK) {
    		//handle cleanup
    	}


		curl_easy_cleanup(curl);
		ss.clear();
	}
}

//private
