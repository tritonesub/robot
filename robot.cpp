#include <iostream>
#include <sstream>
#include <thread>
#include <string>
#include <ifaddrs.h>
#include <stdio.h>
#include <netdb.h>
#include <time.h>

#include "robot.h"
#include "speak.h"
#include "envcanada.h"
#include "face.h"
#include "server.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::shared_ptr;

//private constructors
Robot::Robot() : halt(false), server(*this, 8080) {
	init();
}

Robot::~Robot() {
}

//public methods
int Robot::run() 
{
	Speak& voice = Speak::getInstance();
	Face& face = Face::getInstance();
	voice.say(shared_ptr<const string>(new string("at your service")));

	time_t rawtime;
	int minutes = 60;
	struct tm* timeinfo = NULL;
	
	while(!halt) {
		face.pan(1000);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		face.pan(2000);
		std::this_thread::sleep_for(std::chrono::seconds(1));

		Robot::speakTime();
		
		rawtime = time(NULL);
		minutes = 60;
		if(rawtime != -1) {
			timeinfo = localtime(&rawtime);
			minutes -= timeinfo->tm_min;
		}
		face.pan(1550);
		std::this_thread::sleep_for(std::chrono::minutes(minutes));
	}
	
	voice.say(shared_ptr<const string>(new string("No disassemble!")));
	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}

//private methods
void Robot::init() 
{
	//face test
	Face& face = Face::getInstance();
	face.tilt(1700);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	face.pan(1550);

	face.setColor(DARK_BLUE,RIGHT_EYE);
	face.setColor(ORANGE,LEFT_EYE);
	face.setColor(YELLOW,RIGHT_MOUTH);
	face.setColor(GREEN,CENTER_RIGHT_MOUTH);
	face.setColor(TURQUOISE,CENTER_MOUTH);
	face.setColor(PURPLE,CENTER_LEFT_MOUTH);
	face.setColor(PINK,LEFT_MOUTH);
	face.pan(2500);

	std::this_thread::sleep_for(std::chrono::seconds(4));
	face.pan(600);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	face.pan(1550);

	std::this_thread::sleep_for(std::chrono::seconds(2));
	face.setColor(DARK_BLUE, EYES);
	face.setColor(PINK, MOUTH);

	Speak& voice = Speak::getInstance();
	shared_ptr<string> ip;
	if(Robot::getIP(ip) == 0) {
		voice.say(shared_ptr<const string>(new const string("I am connected to the internet with the address...")));
		voice.say(ip);
	}
	else {
		voice.say(shared_ptr<const string>(new const string("I am not connected to the internet.")));
	}




//	EnvCanada weather("ns-19_e");
}

void Robot::handleRequest(string const &req, string &resp) 
{
	resp = "got it";
}

void Robot::speakTime() 
{
	Speak& voice = Speak::getInstance();
	time_t rawtime = time(NULL);

	if(rawtime != -1) {
		struct tm* timeinfo;
		timeinfo = localtime(&rawtime);
		shared_ptr<const string> msg;
		shared_ptr<const string> msg2;

		if(timeinfo->tm_hour < 6)
			msg = shared_ptr<const string>(new const string("I can't believe you're awake!"));
		else if(timeinfo->tm_hour < 12)
			msg = shared_ptr<const string>(new const string("Good morning!"));
		else if(timeinfo->tm_hour < 17)
			msg = shared_ptr<const string>(new const string("Good afternoon!"));
		else if(timeinfo->tm_hour < 22)
			msg = shared_ptr<const string>(new const string("Good evening!"));
		else
			msg = shared_ptr<const string>(new const string("It's getting late!"));
		
		voice.say(msg);
		stringstream ss;
		string time;

		ss << "It is ";
		if(timeinfo->tm_hour > 12) {
			time = std::to_string(timeinfo->tm_hour - 12); 
		}
		else if (timeinfo->tm_hour == 0){
			time = "midnight";
		}
		else {
			time = std::to_string(timeinfo->tm_hour);
		}
		if(timeinfo->tm_min == 0) {
			ss << time;
			if(timeinfo->tm_hour != 0) {
				ss << " o\' clock"; 
			}
		}
		else {
			ss << timeinfo->tm_min << " minutes after " << time;
		}

		msg2 = shared_ptr<const string>(new const string(ss.str()));

		voice.say(msg2);
		ss.clear();
	}
	return;
}

int Robot::getIP(shared_ptr<string>& ip) 
{
	struct ifaddrs* ifaddr;

	if(getifaddrs(&ifaddr) == -1) {
	    perror("getifaddrs");	
		return -1;
	}

	struct ifaddrs* i = ifaddr;

	for(i = ifaddr; i != NULL; i = i->ifa_next) {
		if(i->ifa_addr == NULL) 
			continue;
		
		int family = i->ifa_addr->sa_family;

		if(family == AF_INET) {
			char host[NI_MAXHOST];
			int status = getnameinfo(i->ifa_addr, sizeof(struct sockaddr_in),
							host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
			if(status == 0) {
		  		ip = shared_ptr<string>(new string(host));
			}
		}
	}

	freeifaddrs(ifaddr);

	return 0;
}

