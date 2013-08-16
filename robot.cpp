#include <iostream>
#include <sstream>
#include <ifaddrs.h>
#include <stdio.h>
#include <netdb.h>
#include <time.h>

#include "robot.h"
#include "speak.h"
#include "envcanada.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

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
	voice.say("at your service");
	while(!halt) {

	}
	voice.say("No disassemble!");
	return 0;
}

//private methods
void Robot::init() 
{
	Speak& voice = Speak::getInstance();
	string ip;
	if(Robot::getIP(ip) == 0) {
		voice.say("I am connected to the internet with the address...");
		voice.say(ip);
	}
	else {
		voice.say("I am not connected to the internet.");
	}

	time_t rawtime;
	time(&rawtime);

	if(rawtime != -1) {
		struct tm* timeinfo;
		timeinfo = localtime(&rawtime);

		if(timeinfo->tm_hour < 5)
			voice.say("I can't believe you're awake!");
		else if(timeinfo->tm_hour < 12)
			voice.say("Good morning!");
		else if(timeinfo->tm_hour < 17)
			voice.say("Good afternoon!");
		else if(timeinfo->tm_hour < 20)
			voice.say("Good evening!");
		else
			voice.say("It's getting late!");

		stringstream ss;
		ss << "It is " << timeinfo->tm_min << " minutes after ";

		if(timeinfo->tm_hour < 12 && timeinfo->tm_hour > 0)
			ss << timeinfo->tm_hour;
		if(timeinfo->tm_hour > 12)
			ss << timeinfo->tm_hour - 12;
		else
			ss << " midnight";

		voice.say(ss.str());
		ss.clear();
	} 

//	EnvCanada weather("ns-19_e");
}

int Robot::getIP(string& ip) 
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
		  		ip = host;
			}
		}
	}

	freeifaddrs(ifaddr);

	return 0;
}

