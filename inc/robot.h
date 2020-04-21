#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <memory>
#include "ServerHandler.h"
#include "server.h"

class Robot:public ServerHandler {

public:

	//constructors
	Robot();
	~Robot();

	//methods
	int run();

private:
	
	bool halt;
	Server server;

	//methods
	void init();	
	void handleRequest(std::string const &req, std::string &resp) override;


	//static
	static int getIP(std::shared_ptr<std::string>& ip);
	static void speakTime();
};

#endif //robot.h
