#include <iostream>
#include <sstream>
#include <thread>
#include <ifaddrs.h>
#include <stdio.h>
#include <netdb.h>
#include <time.h>

#include "robot.h"
#include "speak.h"
#include "envcanada.h"
#include "face.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::shared_ptr;

//private constructors
Robot::Robot():halt(true) {
	init();
}

Robot::~Robot() {
}

//public methods
int Robot::run() 
{
	Speak& voice = Speak::getInstance();
	voice.say(shared_ptr<const string>(new string("at your service")));
	while(!halt) {

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
	face.pan_tilt(1550,1700);

	Speak& voice = Speak::getInstance();
	shared_ptr<string> ip;
	if(Robot::getIP(ip) == 0) {
		voice.say(shared_ptr<const string>(new const string("I am connected to the internet with the address...")));
		voice.say(ip);
	}
	else {
		voice.say(shared_ptr<const string>(new const string("I am not connected to the internet.")));
	}

	face.pan(2500);
	std::this_thread::sleep_for(std::chrono::seconds(4));
	time_t rawtime = time(NULL);

	if(rawtime != -1) {
		struct tm* timeinfo;
		timeinfo = localtime(&rawtime);
		shared_ptr<const string> msg;

		if(timeinfo->tm_hour < 5)
			msg = shared_ptr<const string>(new const string("I can't believe you're awake!"));
		else if(timeinfo->tm_hour < 12)
			msg = shared_ptr<const string>(new const string("Good morning!"));
		else if(timeinfo->tm_hour < 17)
			msg = shared_ptr<const string>(new const string("Good afternoon!"));
		else if(timeinfo->tm_hour < 20)
			msg = shared_ptr<const string>(new const string("Good evening!"));
		else
			msg = shared_ptr<const string>(new const string("It's getting late!"));
		
		voice.say(msg);

		stringstream ss;
		ss << "It is " << timeinfo->tm_min << " minutes after ";

		if(timeinfo->tm_hour < 12 && timeinfo->tm_hour > 0)
			ss << timeinfo->tm_hour;
		else if(timeinfo->tm_hour > 12)
			ss << timeinfo->tm_hour - 12;
		else
			ss << " midnight";


		msg = shared_ptr<const string>(new const string(ss.str()));

		voice.say(msg);
		ss.clear();
	    face.pan(600);

		std::this_thread::sleep_for(std::chrono::seconds(5));
		face.pan_tilt(1550,900);
	} 

//	EnvCanada weather("ns-19_e");
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

